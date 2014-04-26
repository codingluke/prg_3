import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class KeyController
{
  /**
   * The available specialchars for the keyword.
   */
  private static final String SPECIALCHARS = "@#$%-+?!:/_¢^~`";

  /**
   * Regex pattern for validating keyword strength.
   * Keyword must include at least:
   * - one small letter
   * - one big letter
   * - one digit
   * - one Specialchrar defined in SPECIALCHARS
   * - between 10 and 20 chars long.
   */
  private static final String KEY_PATTERN =
    "^(?=.*\\d)(?=.*[a-z])(?=.*[A-Z])(?=.*[" + SPECIALCHARS + "])" +
    "[A-z\\d" + SPECIALCHARS + "]{10,}+$";

  /**
   * Pivate constructor to prevent instances of this Class.
   */
  private KeyController()
  {
  }

  /**
   * Validateds if the given Keyword is accurate.
   *
   * @param key   Key to test for streangthness.
   *
   * @return boolean if key is strong enougth or not.
   */
  public static boolean validateKeyStreangth(String key)
  {
    Pattern pattern = Pattern.compile(KEY_PATTERN);
    Matcher matcher = pattern.matcher(key);
    return matcher.matches();
  }

  /**
   * Adapt the key to a given length.
   *
   * @param key     key to adapt.
   * @param length  length of the generated key.
   *
   * @return new key in the length of lenght.
   */
  public static String generateAdaptedKey(String key, int length)
  {
    return key;
  }

  /**
   * Gives back the SPECIALCHARS..
   */
  public static String getSpecialchars()
  {
    return SPECIALCHARS;
  }
}
