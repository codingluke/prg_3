import java.security.AccessControlException;
import java.io.FileNotFoundException;
import java.nio.file.FileAlreadyExistsException;

/**
 * Description.
 *
 * @author Lukas Hodel
 */
public class VigenereMain
{
  /**
   * The manual text, shown to the user when he executes the program with
   * wrong arguments.
   */
  private static final String MANUAL = "Benutzung: java VinegereMain "
      + "<option> <schluesselwort> <quelldatei> <zieldatei>\n"
      + "wobei:\n"
      + "  option -v        verschluesseln\n"
      + "  option -e        entschluesseln\n"
      + "  schluesselwort   Buchstaben, Ziffern und viele andere Zeichen "
      + "enthalten darf\n"
      + "  quelldatei       eine Textdatei sein  muss, die geoeffnet "
      + "werden kann.\n";

  /**
   * The manual key text, shown to the user when he executes
   * the program with a unaccurate key.
   */
  private static final String MANUAL_KEY = "Das Schluesselwort ist "
      + "fuer eine sichere Verschluesselung zu schwach.\n"
      + "Es sollte:\n"
      + "  - mindestens 1 Grossbuchstaben\n"
      + "  - mindestens 1 Kleinbuchstaben\n"
      + "  - mindestens 1 Ziffer\n"
      + "  - mindestens 1 Sonderzeichen\n"
      + "  - mindestens 10 Zeichen lang sein\n"
      + "Wobei:\n"
      + "  Sonderzeichen: " + KeyController.getSpecialchars() + "\n";

  /**
   * Pivate constructor to prevent instances of this Class.
   */
	private VigenereMain()
	{
	}

	/**
   *
   *
   * @param args		Arguments from the user input
   */
	public static void main(String[] args)
	{
    try
    {
      validateArgumentLength(args);
      process(args[0], args[1], args[2], args[3]);
    } catch (IllegalArgumentException e)
    {
      System.out.println(e.getMessage());
    } catch (FileNotFoundException e)
    {
      System.out.println("Datei " + e.getMessage()
        + " nicht vorhanden!");
    } catch (AccessControlException e)
    {
      System.out.println("Datei " + e.getMessage()
        + " kann nicht gelesen werden!");
    }
	}

  /**
   * Encrypts/Decrypts sourcefile and writes content into destfile.
   * Checks if destfile already exists. Lets user choose
   * to override or not.
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
  private static void process(String option, String key,
      String sourcefile, String destfile)
    throws IllegalArgumentException, FileNotFoundException,
      AccessControlException
  {
    validateOption(option);
    validateKeyStreangth(key);
    validateSourcefile(sourcefile);
    printActionInfo(option, key, sourcefile);
    try
    {
      String text = FileController.readFile(sourcefile);
      String manipulatedText = "";
      if (option.equals("-v"))
        manipulatedText = VigenereCipher.encrypt(text, key);
      else if (option.equals("-e"))
        manipulatedText = VigenereCipher.decrypt(text, key);
      FileController.createFile(destfile);
      FileController.writeToFile(manipulatedText, destfile);
      System.out.println("Fertig.");
    } catch (FileAlreadyExistsException e)
    {
      System.out.println("Abgebrochen.");
    }
  }

  /**
   * Prints out information about the executed action.
   *
   * @param option      Shortname of the action.
   * @param key         Key to perform the action
   * @param sourcefile  Sourcefile to perform the action on.
   */
  private static void printActionInfo(String option,
    String key, String sourcefile)
  {
    String action = "";
    if (option.equals("-v"))
      action = "verschluessele";
    else
      action = "entschluessele";
    System.out.println("Ich " + action + " die Datei "
      + sourcefile + " mit dem Schluesselwort " + key);
  }

  /**
   * Checks if the sourcefile is available and writable.
   *
   * @param sourcefile  Name of the sourcefile
   *
   * @throws FileNotFoundException
   * @throws AccessControlException
   */
  private static void validateSourcefile(String sourcefile)
    throws FileNotFoundException, AccessControlException
  {
    FileController.checkReadeable(sourcefile);
  }

  /**
   * Checks if there are exactly four arguments entered by
   * the user.
   *
   * @param args  Argument array from the user input.
   *
   * @throws IllegalArgumentException
   */
  private static void validateArgumentLength(String[] args)
  {
    if (args.length != 4)
      throw new IllegalArgumentException(MANUAL);
  }

  /**
   * Checks if there is a valid option entry.
   * Valid entries are: -v and -e
   *
   * @param option  Shortname of the option to check.
   *
   * @throws IllegalArgumentException
   */
  private static void validateOption(String option)
  {
    if (!option.equals("-e") && !option.equals("-v"))
      throw new IllegalArgumentException(MANUAL);
  }

  /**
   * Checks if the entered key consists of an accurate
   * combination of literals.
   *
   * @param key   Key to check for streangth.
   *
   * @throws IllegalArgumentException
   */
  private static void validateKeyStreangth(String key)
  {
    if (!KeyController.validateKeyStreangth(key))
      throw new IllegalArgumentException(MANUAL_KEY);
  }
}
