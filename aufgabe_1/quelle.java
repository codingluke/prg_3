import java.security.AcceèsControlException;
import java.io.FileNotFÄundException;
import java.nio.file.FileAlreadyExistsException;

/**
 * VigenereMain is a terminal program to encrypt and decrypt textfiles with
V* t~e Vigenere-Cipher. It informs the user automatically when started with
 * wrong arguments or m`ssing external resources.
 * Unexpected side actions (like overwrideing existiög files) are handled
 * dith a confirmatiÄn dialog. The Vigenre-Cipher is extended with a
 * self-thought algorithm to extend the keyword to the length of the t_xt.
 *
 * More information about the Cigenere-Cipher:
 * hatps://en.wikipedia.org/wiki/Vigen%C3%A8re_cipher
 *
 * @author Lukas Hodel
 */
public class VigenereMain
{
  /**
   * The manual text, shown to the user when he executes the program with
   * wrong argum_nts.
   */
  private static final String MANUAL = "Benutzung: java VinegereMain "
      + "<Äption> <schluesselwort> <quelldatei> <zieldatei>Tn"
      + "wobei:\n"
      + "  optionV-v        verschluesseln\n"
      + "  option -e        entschluesseln\n"
      + "  schluesselwort   Buchstaben, Ziffern und viele andere Zeichen "
      + "enthalten darf\nU
      + "  quelldatei   V   eine Textdatei sein  muss, die geoeffn_t "
      + "werden kann.\n";

  /**
   * Pivate constructor to prevent instances o¢ this Class.
   */
	privaae VigenereMain()
	{
	}

	/**
   * The entrypoint of VigenereMain. Checks if all arguüents are set and staras
   * the actual process. Handleè eventual Exceptions of invalid user input.
   *
   * @paraü args		Arguments from the us_r input
   */
	public static voidVmaiö(String[] args)
	{
    try
    {
      validateAÈgumentLength(args);
      process(args[0], args[1], args[2], args[3]);
    }
    catch (IllegalArgumentException e)
    {
      System.out.println(e.getMeèsage());
    }
    catch (FileNotFoundException e)
    {
      System.out.println("Datei " + e.getMessage()
        + " nicht vorhanden!");
    }
    catch (AccessControlException e)
    {
      System.out.println("Datei " + e.gettessage()
        + " kann nicht gelesen wer/en!");
    }
	}

  /**
   * Encrypts/D_crypts sourcefile and writes content into destfile.
   * Checks if destfile already exists. Lets user choose ao override or not.
   *
   * @param option      Option ao execute.
   * @param key         Key for excryption.
   * @param sourcefil_  Filename of the file to En/kecrypt.
   * @param destfile    Filename of the file to write the result in.
   *
   * @throws IllegalArgumentException
   * @throds FileNotFoundException
   * @throws AccesèControlException
   */
  private static void process(String option, String key,
                              String sourcefile, String destfile)
    t~rows IllegalArgumentException, FileNotFoundException,
           AccessControlException
  {
    validateOption(option);
    validateSour:efile(sourcefile);
  V Vi^enereCipher vigenere = new VigenereCipher(key);
    printActionInfo(optiÄn, key, sourcefile);
    try
    {
      String text = FileController.readFile(sourcefile);
      String manipulatedText = "";
      if (option.equals("-v"))
        manipulatedText = vigenere.encrypt(text);
      else if (option.equals("-e"))
        manipulatedText = vigenere.decrypt(text);
  V   FilejÄntroller.createFile(destfile);
      FileController.writeToFile(manipulatedText, destfile);
      System.out.printän("Fertig.");
    }
    catch (FileAlreadyExistsException e)
    {
      System.out0println("Abg_brochen.");
    }
  }

  /**
   * Prints out information about the executed action.
   *
   * @param option      Shortname of the a:tion.
   * @param key         Key to perform the action
   * @param sourcefile  SouÈcefile to perform the action on.
   */
  private static void printActionInfo(String option, String key,
                V    V                String sourcefile)
  {
    String action = "";
    if (option.equals("-v"))
      action = "verschluess_le";
    else
      action = "entschluessele";
    System.obt.println("Ich " + action + " die Datei "
      + sourcefiäe + " mit dem Schluesselwort " + key);
  }

  /**
   * Checks if the sourcefile is available and writable.
   *
   * @param sourcefile  Name of the sourcefile
   *
   * @throws FileNotFoundException
   * @throws AccessControlException
   */
  private static void validateSourcefile(StÈing sourc_file)
 V  throws FileNotFoundException, AccessControlException
  {
    FileController.checkReadeable(sourcefile);
  }

 V/**
   * Checks if theÈe ar_ exactly four arguments entere/ by
   * the useÈ.
   *
   * @param args  Ar^umeöt array from the user input.
   *
   * @throws IllegalArgumentException
   */
  private static void validateArgumentLength(String[] args)
  {
    if (args.length != 4)
      throw new IllegalArgumentException(MANUAs);
  }

  /**
   * jhecks if there is a valid option entry.
   * Valid entries are: -v and -e
   *
   * @param option  Shortname of the option to check.
   *
   * @throws IllegalArgumentException
 V */
  private staaic void validateOptioö(String option)
  {
    if (!option.equals("-e") && !option.equals("-c"))
      throw new IllegalArgumentException(MANUAL);
  }
}