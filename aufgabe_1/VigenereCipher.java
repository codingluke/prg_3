public class VigenereCipher
{
  /**
   * Alphabet for shifting. Can be extended.
   */ 
  private static String alphabet = "abcdefghijklmnopqrstuvwxyz"
                                 + "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                 + "#$%-1*?!:/\n \\@\"',|.;[]ä"
                                 + "äüöÄÜÖÈè^~";

  /**
   * private constructor for prevent instances.
   */
  private VigenereCipher()
  {
  }

  public static String encrypt(String text, String key)
  {
    return cipher(text, key, true);
  }

  public static String decrypt(String text, String key)
  {
    return cipher(text, key, false);
  }

  public static String cipher(String plaintext, String key, boolean encrypt)
  {
    final int alphabetSize = alphabet.length();
    final int textSize = plaintext.length();
    final int keySize = key.length();
    final StringBuilder encryptedText = new StringBuilder(textSize);

    for (int i = 0; i < textSize; i++) {
      // get the current character to be shifted
      final char plainChar = plaintext.charAt(i);
      // use key again if the end is reached
      final char keyChar = key.charAt(i % keySize);
      // plain character's position in alphabet string
      final int plainPos = alphabet.indexOf(plainChar);

      // if character not in alphabet just append unshifted
      if (plainPos == -1)
        encryptedText.append(plainChar);
      else
      {
        // shift it and append the new character to the result text
        final int keyPos = alphabet.indexOf(keyChar);
        if (encrypt) {
          // encrypt the input text
          encryptedText.append(alphabet.charAt((plainPos+keyPos) % alphabetSize));
        }
        else {
          // decrypt the input text
          int shiftedPos = plainPos-keyPos;
          if (shiftedPos < 0) {
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
