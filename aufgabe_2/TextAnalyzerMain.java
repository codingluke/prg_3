import java.security.AccessControlException;
import java.io.FileNotFoundException;
import java.nio.file.FileAlreadyExistsException;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map.Entry;
import java.io.FileReader;

/**
 * TODO : Cleanup main!!
 *
 * VigenereMain is a terminal program to encrypt and decrypt textfiles with
 * the Vigenere-Cipher. It informs the user automatically when started with
 * wrong arguments or missing external resources.
 * Unexpected side actions (like overwrideing existing files) are handled
 * with a confirmation dialog. The Vigenre-Cipher is extended with a
 * self-thought algorithm to extend the keyword to the length of the text.
 *
 * More information about the Cigenere-Cipher:
 * https://en.wikipedia.org/wiki/Vigen%C3%A8re_cipher
 *
 * @author Lukas Hodel
 */
public class TextAnalyzerMain
{
  /**
   * The manual text, shown to the user when he executes the program with
   * wrong arguments.
   */
  private static final String MANUAL = "Benutzung: "
    + "java TextAnalyzerMain <textdatei>";

  /** Object responsible for text analyzation. */
  private static TextAnalyzer analyzer;

  /**
   * Pivate constructor to prevent instances of this Class.
   */
	private TextAnalyzerMain()
	{
	}

	/**
   * The entrypoint of VigenereMain. Checks if all arguments are set and starts
   * the actual process. Handles eventual Exceptions of invalid user input.
   *
   * @param args		Arguments from the user input
   */
	public static void main(String[] args)
	{
    try
    {
      validateArgumentLength(args);
      if (loadFileIntoAnalyzer(args[0]))
        actionHandle();
    }
    catch (IllegalArgumentException e)
    {
      System.out.println(e.getMessage());
    }
	}

  /**
   * Reads a file with FileController and instantiates a new TextAnalyzer
   * with this file. When everything was successfull it returns true,
   * otherwise false. The file handling completely delegated to the
   * class FileController as method openFile.
   *
   * @param filename  The filename of the file to load into the TextAnalyzer.
   *
   * @return Boolean true or false if successfull or not.
   */
  private static boolean loadFileIntoAnalyzer(String filename)
  {
    boolean state = false;
    FileReader reader = FileController.openFile(filename);
    if (reader != null)
    {
      analyzer = new TextAnalyzer(reader);
      state = true;
    }
    return state;
  }

  /**
   * Reads filename from user input and reads afterward the file with
   * the given filename into the analyzer.
   */
  private static void loadFileIntoAnalyzer()
  {
    String filename = ConsoleInput.readString("Bitte filename angeben: ");
    loadFileIntoAnalyzer(filename);
  }

  /**
   * Encrypts/Decrypts sourcefile and writes content into destfile.
   * Checks if destfile already exists. Lets user choose to override or not.
   *
   * @param option      Option to execute.
   * @param key         Key for excryption.
   * @param sourcefile  Filename of the file to En/Decrypt.
   * @param destfile    Filename of the file to write the result in.
   *
   * @throws IllegalArgumentException
   * @throws FileNotFoundException
   * @throws AccessControlException
   */
  private static void actionHandle()
  {
    int action;
    do
    {
      printActions();
      action = ConsoleInput.readInt("Bitte Auswahl treffen: ", 1, 13);
      if (action == 1)
        sortAndPrintAsc();
      else if (action == 2)
        sortAndPrintAscInterval();
      else if (action == 3)
        sortAndPrintDesc();
      else if (action == 4)
        sortAndPrintDescInterval();
      else if (action == 5)
        sortAndPrintDescByValue();
      else if (action == 6)
        sortAndPrintDescIntervalByValue();
      else if (action == 7)
        sortAndPrintAscByValue();
      else if (action == 8)
        sortAndPrintAscIntervalByValue();
      else if (action == 9)
        printWordCount();
      else if (action == 10)
        writeWordList();
      else if (action == 11)
        loadFileIntoAnalyzer();
      else if (action == 12)
        showFile();
      else if (action == 13)
        System.out.println("Byebye");
    } while (action != 13);
  }

  /**
   * Sorts the wordlist ascending by key (words) and prints the
   * wordlist to the console.
   */
  private static void sortAndPrintAsc()
  {
    sortAndPrint(true, true, false);
  }

  /**
   * Sorts the wordlist ascending by value (word count) and prints the
   * wordlist to the console.
   */
  private static void sortAndPrintAscByValue()
  {
    sortAndPrint(false, true, false);
  }

  /**
   * Promts the user to input an interval, sorts the wordlist
   * ascending by key (words), filters the worldlist with the interval
   * and prints the wordlist to the console.
   */
  private static void sortAndPrintAscInterval()
  {
    sortAndPrint(true, true, true);
  }

  /**
   * Promts the user to input an interval, sorts the wordlist
   * ascending by value (word count), filters the worldlist with the interval
   * and prints the wordlist to the console.
   */
  private static void sortAndPrintAscIntervalByValue()
  {
    sortAndPrint(false, true, true);
  }

  /**
   * Sorts the wordlist descending by keys (words) and prints the
   * wordlist to the console.
   */
  private static void sortAndPrintDesc()
  {
    sortAndPrint(true, false, false);
  }

  /**
   * Sorts the wordlist descending by values (word count) and prints the
   * wordlist to the console.
   */
  private static void sortAndPrintDescByValue()
  {
    sortAndPrint(false, false, false);
  }

  /**
   * Promts the user to input an interval, sorts the wordlist
   * descending by Key, filters the worldlist with the interval
   * and prints the wordlist to the console.
   */
  private static void sortAndPrintDescInterval()
  {
    sortAndPrint(true, false, true);
  }

  /**
   * Promts the user to input an interval, sorts the wordlist
   * descending by Value, filters the worldlist with the interval
   * and prints the wordlist to the console.
   */
  private static void sortAndPrintDescIntervalByValue()
  {
    sortAndPrint(false, false, true);
  }

  /**
   * Sorts the wordlist according the parameters and prints it to the console.
   * When interval is set, it promts the user to input the min and max bound of
   * the interval. When is given the wordlist gets also filtered the words
   * occurence, in between the the interval.
   *
   * @param byKey     Sort by key or value. key = words, value = wordcount.
   * @param asc       Sort direction true = asc, false = desc.
   * @param interval  Filtered interval or not.
   *
   * @return
   */
  private static void sortAndPrint(boolean byKey, boolean asc, boolean interval)
  {
    if (interval)
    {
      int min = ConsoleInput.readInt("Bitte min bestimmen: ");
      int max = ConsoleInput.readInt("Bitte max bestimmen: ");
      analyzer.sort(byKey, asc, min, max);
    }
    else
      analyzer.sort(byKey, asc);
    printWordList(analyzer.getCurrentWordMap());
  }

  /**
   * Prints the total word count of the current Wordlist to the console.
   */
  private static void printWordCount()
  {
    System.out.println("Die Liste enthaelt " + analyzer.currentSize()
                       + " Woerter");
  }

  /**
   * Reads a filename from the console, reads the file according the filename
   * and prints its content to the console. If the file is not available, an
   * error gets printet to the console.
   */
  private static void showFile()
  {
    String filename = ConsoleInput.readString("Bitte filename angeben: ");
    FileController.showFile(filename);
  }

  /**
   * Prints the actual wordlist line by line to the terminal.
   * Format: "word1                   1\n"
   */
  private static void writeWordList()
  {
    String filename = ConsoleInput.readString("Bitte filename angeben: ");
    try
    {
      FileController.createFile(filename);
      FileController.writeToFile(analyzer.toString(), filename);
    }
    catch (FileAlreadyExistsException e)
    {
      System.out.println("Abgebrochen.");
    }
  }

  /**
   * Prints the wordlist to the console.
   *
   * @param wordMap   Wordlist as a HashMap.
   */
  private static void printWordList(HashMap wordMap)
  {
    Iterator it = wordMap.entrySet().iterator();
    while (it.hasNext()) {
      Entry pairs = (Entry)it.next();
      String format = "%1$-25s%2$d%n";
      System.out.format(format, pairs.getKey(), pairs.getValue());
    }
  }

  /**
   * Prints out information about the executed action.
   *
   * @param option      Shortname of the action.
   * @param key         Key to perform the action
   * @param sourcefile  Sourcefile to perform the action on.
   */
  private static void printActions()

  {
    String info = "(1)  Woerter aufsteigend alphabetisch sortiert\n";
    info += "(2)  Woerter mit Haeufigkeit von min bis max aufsteigend ";
    info += "alphabetisch sortiert\n";
    info += "(3)  Woerter absteigend alphabetisch sortiert\n";
    info += "(4)  Woerter mit Haeufigkeit von min bis max absteigend ";
    info += "alphabetisch sortiert\n";
    info += "(5)  Woerter absteigend nach Haeufigkeit sortiert\n";
    info += "(6)  Woerter mit Haeufigkeit von min bis max absteigend nach ";
    info += "Haeufigkeit sortiert\n";
    info += "(7)  Woerter aufsteigend nach Haeufigkeit sortiert\n";
    info += "(8)  Woerter mit Haeufigkeit von min bis max aufsteigend nach ";
    info += "Haeufigkeit sortiert\n";
    info += "(9)  Anzahl Woerter feststellen\n";
    info += "(10) Woerterliste speichern\n";
    info += "(11) Neue Woerterliste erzeugen\n";
    info += "(12) Textdatei anzeigen\n";
    info += "(13) Programm beenden";
    System.out.println(info);
  }

  /**
   * Checks if there are exactly one argument entered by
   * the user.
   *
   * @param args  Argument array from the user input.
   *
   * @throws IllegalArgumentException
   */
  private static void validateArgumentLength(String[] args)
  {
    if (args.length != 1)
      throw new IllegalArgumentException(MANUAL);
  }
}
