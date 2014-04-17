import java.util.regex.Matcher;
import java.util.regex.Pattern;
import java.security.AccessControlException;
import java.io.FileNotFoundException;

/**
 * Description.
 * TODO : Check if destfile already exists.
 * TODO : Let user chose if overwrite or not.
 * TODO : Key to the same length than text algorithm.
 * TODO : COMMENTING!
 *
 * @author Lukas Hodel
 */
public class VigenereMain
{
  private static String option;

  private static String key;

  private static String sourcefile;

  private static String destfile;

  private static final String SPECIALCHARS = "@#$%-+*?!:/";

  /**
   * Regex pattern for validating keyword strength.
   * Keyword must include at least:
   * - one small letter
   * - one big letter
   * - one digit
   * - one Specialchra defined in SPECIALCHARS
   * - between 10 and 20 chars long.
   */
  private static final String KEY_PATTERN =
    "((?=.*\\d)(?=.*[a-z])(?=.*[A-Z])(?=.*[" + SPECIALCHARS + "]).{10,20})";

  /**
   * The manual text, shown to the user when he executes
   * the program with wrong arguments.
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
   * The manual text, shown to the user when he executes
   * the program with wrong arguments.
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
      + "  Sonderzeichen: " + SPECIALCHARS + "\n";

	/**
   * Private constructor to prevent instances of this Class.
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
      readAndValidateArguments(args);
      if (option.equals("-v"))
        encrypt();
      else
        decrypt();
    } catch (IllegalArgumentException e)
    {
      System.out.println(e.getMessage());
    } catch (AccessControlException e)
    {
      System.out.println(e.getMessage());
    } catch (FileNotFoundException e)
    {
      System.out.println(e.getMessage());
    }
	}

  /**
   * Encrypts sourcefile and writes into destfile.
   */
  private static void encrypt()
    throws FileNotFoundException, AccessControlException, IllegalArgumentException
  {
    System.out.println("Verschluesseln");
    String text = FileController.readFile(sourcefile);
    String encrypted = VigenereCipher.encrypt(text, key);
    FileController.writeToFile(encrypted, destfile);
  }

  /**
   * Decrypts sourcefile and writes into destfile.
   */
  private static void decrypt()
    throws FileNotFoundException, AccessControlException, IllegalArgumentException
  {
    System.out.println("Entschluesseln");
    String text = FileController.readFile(sourcefile);
    String decrypted = VigenereCipher.decrypt(text, key);
    FileController.writeToFile(decrypted, destfile);
  }

  /**
   * Validates the arguments. When there is an input failure
   * an IllegalArgumentException is thrown.
   *
   * @param args  Arguments from the execution.
   *
   * @exception   IllegalArgumentException
   * @exception   AccessControlException
   * @exception   FileNotFoundException
   */
  private static void readAndValidateArguments (String[] args) throws FileNotFoundException, AccessControlException, IllegalArgumentException
  {
    if (args.length != 4)
      throw new IllegalArgumentException(MANUAL);

    readArguments(args);

    if (!option.equals("-e") && !option.equals("-v"))
      throw new IllegalArgumentException(MANUAL);
    else if (!validateKeyStreangth(key))
      throw new IllegalArgumentException(MANUAL_KEY);

    FileController.checkReadeable(sourcefile);
  }

  /**
   * Reads the arguments and saves thim in their
   * specific fields; option, key and sourcefile.
   */
  private static void readArguments(String[] args)
  {
    option = args[0];
    key = args[1];
    sourcefile = args[2];
    destfile = args[3];
  }

  /**
   * Validateds if the given Keyword is accurate.
   *
   * @param key   Key to test for streangthness.
   *
   * @return boolean if key is strong enougth or not.
   */
  private static boolean validateKeyStreangth(String key)
  {
    Pattern pattern = Pattern.compile(KEY_PATTERN);
    Matcher matcher = pattern.matcher(key);
    return matcher.matches();
  }
}
