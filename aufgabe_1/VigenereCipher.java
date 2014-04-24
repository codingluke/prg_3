public class VigenereCipher
{
  /**
   * Alphabet for shifting. Can be extended.
   */
  private static String alphabet = "abcdefghijklmnopqrstuvwxyz"
                                 + "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                 + "123456789"
                                 + "#$%-*?!:/\n \\@\"',|.;[]_"
                                 + "äüöÄÜÖÈè^~\t";

  /**
   * private constructor for prevent instances.
   */
  private VigenereCipher()
  {
  }

  /**
   * Encrypts a text with the VigenereCipher.
   *
   * @param text    Text to decrypt.
   * @param key     Key for the algorithm.
   *
   * @return with vigenere-algorithm encrypted text.
   */
  public static String encrypt(String text, String key)
  {
    return cipher(text, extendKey(key, text.length()), true);
  }

  /**
   * Decrypts a text with the vigenere algorithm.
   *
   * @param text    Text to decrypt.
   * @param key     Key for the algorithm.
   *
   * @return with vigenere-algorithm decrypted text.
   */
  public static String decrypt(String text, String key)
  {
    return cipher(text, extendKey(key, text.length()), false);
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
  private static String extendKey(String key, int length)
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
   * @return with VigenereCipher algorithm de/encrypted text.
   */
  private static String cipher(String plaintext, String key, boolean encrypt)
  {
    final int alphabetSize = alphabet.length();
    final int textSize = plaintext.length();
    final int keySize = key.length();
    final StringBuilder encryptedText = new StringBuilder(textSize);
    for (int i = 0; i < textSize; i++)
    {
      final char plainChar = plaintext.charAt(i);
      final char keyChar = key.charAt(i % keySize);
      final int plainPos = alphabet.indexOf(plainChar);
      if (plainPos == -1)
      {
        // if character not in alphabet just append unshifted
        encryptedText.append(plainChar);
      }
      else
      {
        // shift it and append the new character to the result text
        final int keyPos = alphabet.indexOf(keyChar);
        if (encrypt)
        {
          int shiftedPos = (plainPos + keyPos) % alphabetSize;
          encryptedText.append(alphabet.charAt(shiftedPos));
        }
        else
        {
          // decrypt the input text
          int shiftedPos = plainPos - keyPos;
          if (shiftedPos < 0)
          {
            // negative numbers cannot be handled with modulo
            shiftedPos += alphabetSize;
          }
          encryptedText.append(alphabet.charAt(shiftedPos));
        }
      }
    }
    return encryptedText.toString();
  }
}
