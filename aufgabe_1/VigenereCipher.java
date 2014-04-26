import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class VigenereCipher
{
  /**
   * The available specialchars for the keyword.
   */
  private static final String SPECIALCHARS = "@#$%+?!:/_¢^~`=.-";

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
   * Alphabet for shifting. Can be extended.
   */
  private static final String alphabet = "abcdefghijklmnopqrstuvwxyz"
                                 + "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                 + "0123456789"
                                 + "\n\t\\\" &',|.;*"
                                 + "@#$%-+?!:/_¢^~`=."
                                 + "äüöÄÜÖÈè";

  /**
   * The manual key text, shown to the user when he executes
   * the program with a unaccurate key.
   */
  private static final String MANUAL_KEY = "Das Schluesselwort ist "
      + "fuer eine sichere Verschluesselung zu schwach. Oder es wurden"
      + "ungueltige Zeichen verwendet.\n"
      + "Es sollte:\n"
      + "  - mindestens 1 Grossbuchstaben\n"
      + "  - mindestens 1 Kleinbuchstaben\n"
      + "  - mindestens 1 Ziffer\n"
      + "  - mindestens 1 Sonderzeichen\n"
      + "  - mindestens 10 Zeichen lang sein\n"
      + "Wobei:\n"
      + "  Gueltige Sonderzeichen: " + SPECIALCHARS + "\n";


  /**
   * Key for the encrytion/decryption.
   */
  private String key;

  /**
   * private constructor for prevent instances.
   *
   * @param key                       Key for encryption/decryption
   *
   * @throws IllegalArgumentException when key is not valid
   */
  public VigenereCipher(String key) throws IllegalArgumentException
  {
    setKey(key);
  }

  /**
   * Sets the key for encryption/decryption.
   * Validates key for strongness and valid literals.
   *
   * @param key   Key to encrypt/decrypt
   *
   * @throws IllegalArgumentException
   */
  public void setKey(String key) throws IllegalArgumentException
  {
    if (!validateKey(key))
      throw new IllegalArgumentException(MANUAL_KEY);
    this.key = key;
  }

  /**
   * Encrypts a text with the VigenereCipher.
   *
   * @param text    Text to decrypt.
   *
   * @return with vigenere-algorithm encrypted text.
   */
  public String encrypt(String text)
  {
    String extendedKey = extendKey(this.key, text.length());
    return cipher(text, extendedKey, true);
  }

  /**
   * Decrypts a text with the vigenere algorithm.
   *
   * @param text    Text to decrypt.
   *
   * @return with vigenere-algorithm decrypted text.
   */
  public String decrypt(String text)
  {
    String extendedKey = extendKey(this.key, text.length());
    return cipher(text, extendedKey, false);
  }

  /**
   * Validateds if the given Keyword is accurate and only
   * contains literals available in the alphabet.
   *
   * @param key   Key to test.
   *
   * @return boolean if key is strong enougth or not.
   */
  private boolean validateKey(String key)
  {
    Pattern pattern = Pattern.compile(KEY_PATTERN);
    Matcher matcher = pattern.matcher(key);
    return matcher.matches();
  }

  /**
   * Expands/Mutates a key to a new length.
   * Uses also the VigenereCipher algorithm with the alphabeth as key to
   * generate new key elements. The new keyelements are concatinated until the
   * key reaches a defined length..
   *
   * @param key     Key to expand to the param length.
   * @param length  Length of the new key.
   *
   * @return A key with the length of the param length..
   */
  private String extendKey(String key, int length)
  {
    int times = length / key.length();
    int rest = length % key.length();
    String adaptedKey = "";
    while (adaptedKey.length() < length)
    {
      if (adaptedKey.isEmpty())
        adaptedKey += cipher(key, alphabet, true);
      else
        adaptedKey += cipher(adaptedKey, alphabet, true);
    }
    return adaptedKey.substring(0, Math.min(adaptedKey.length(), length));
  }

  /**
   * Encrypts/Decrypts a text with the VigenereCipher Algorithm.
   *
   * @param plaintext   Text to encrypt/decrypt.
   * @param key         Key for the algorithm.
   * @param encrypt     Boolean to select encrypt/decrypt
   *
   * @return with VigenereCipher encrypted/decrypted text.
   */
  private String cipher(String plaintext, String key, boolean encrypt)
  {
    StringBuilder resultText = new StringBuilder(plaintext.length());
    for (int i = 0; i < plaintext.length(); i++)
    {
      char plainChar = plaintext.charAt(i);
      char keyChar = key.charAt(i % key.length());
      int plainPos = alphabet.indexOf(plainChar);
      if (plainPos == -1)
        resultText.append(plainChar);
      else
      {
        // shift it and append the new character to the result text
        int keyPos = alphabet.indexOf(keyChar);
        if (encrypt)
        {
          int shiftedPos = (plainPos + keyPos) % alphabet.length();
          resultText.append(alphabet.charAt(shiftedPos));
        }
        else
        {
          // decrypt
          int shiftedPos = plainPos - keyPos;
          if (shiftedPos < 0)
            shiftedPos += alphabet.length();
          resultText.append(alphabet.charAt(shiftedPos));
        }
      }
    }
    return resultText.toString();
  }
}
