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
      {
        analyzer.sort();
        printWordList(analyzer.getCurrentMap());
      }
      else if (action == 2)
      {
        int min = ConsoleInput.readInt("Bitte min bestimmen: ", 1, 9999999);
        int max = ConsoleInput.readInt("Bitte max bestimmen: ", 1, 9999999);
        analyzer.sort(min, max);
        printWordList(analyzer.getCurrentMap());
      }
      else if (action == 3)
      {
        analyzer.sort(false);
        printWordList(analyzer.getCurrentMap());
      }
      else if (action == 4)
      {
        int min = ConsoleInput.readInt("Bitte min bestimmen: ", 1, 9999999);
        int max = ConsoleInput.readInt("Bitte max bestimmen: ", 1, 9999999);
        analyzer.sort(false, min, max);
        printWordList(analyzer.getCurrentMap());
      }
      else if (action == 5)
      {
        analyzer.sortByValues(false);
        printWordList(analyzer.getCurrentMap());
      }
      else if (action == 6)
      {
        int min = ConsoleInput.readInt("Bitte min bestimmen: ", 1, 9999999);
        int max = ConsoleInput.readInt("Bitte max bestimmen: ", 1, 9999999);
        analyzer.sortByValues(false, min, max);
        printWordList(analyzer.getCurrentMap());
      }
      else if (action == 7)
      {
        analyzer.sortByValues();
        printWordList(analyzer.getCurrentMap());
      }
      else if (action == 8)
      {
        int min = ConsoleInput.readInt("Bitte min bestimmen: ", 1, 9999999);
        int max = ConsoleInput.readInt("Bitte max bestimmen: ", 1, 9999999);
        analyzer.sortByValues(min, max);
        printWordList(analyzer.getCurrentMap());
      }
      else if (action == 9)
        System.out.println("Die Liste enthaelt "
            + analyzer.currentSize() + " Woerter");
      else if (action == 10)
      {
        String filename = ConsoleInput.readString("Bitte filename angeben: ");
        writeWordList(filename);
      }
      else if (action == 11)
      {
        String filename = ConsoleInput.readString("Bitte filename angeben: ");
        loadFileIntoAnalyzer(filename);
      }
      else if (action == 12)
      {
        String filename = ConsoleInput.readString("Bitte filename angeben: ");
        FileController.showFile(filename);
      }
      else if (action == 13)
        System.out.println("Byebye");
    } while (action != 13);
  }


  /**
   * Prints the actual wordlist line by line to the terminal.
   * Format: "word1                   1\n"
   */
  private static void writeWordList(String filename)
  {
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

  private static void printWordList(HashMap wordList)
  {
    Iterator it = wordList.entrySet().iterator();
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
