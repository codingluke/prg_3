import java.io.FileOutputStream;
import java.io.IOException;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.BufferedWriter;
import java.io.Writer;
import java.io.OutputStreamWriter;

import java.security.AccessControlException;  
import java.util.Scanner;

public class FileController
{
  private FileController()
  {
  }

  /**
   * Checks if a file exists and is readeable according 
   * the filename.
   *
   * @param filename  Name of the file to be checked.
   *
   * @exception AccessControlException
   * @exception FileNotFoundException
   */
  public static void checkReadeable (String filename) 
    throws FileNotFoundException, AccessControlException
  {
    File file = new File(filename);
    checkReadeable(file);
  }
  
  /**
   * Checks if a file exists and is readeable.
   *
   * @param file  File to be checked.
   *
   * @exception AccessControlException
   * @exception FileNotFoundException
   */
  public static void checkReadeable (File file) 
    throws FileNotFoundException, AccessControlException
  {
    if (!file.isFile())
      throw new FileNotFoundException("Quelldatei ist nicht vorhanden!");
    else if (!file.canRead())
      throw new AccessControlException("Quelldatei ist nicht Lesbar!");
  }

  /**
   * Reads a textfile according the filename
   * and returns its contetn.
   *
   * @param filename  Name of the file to read.
   *
   * @return Content of the file.
   */
  public static String readFile(String filename)
    throws FileNotFoundException, AccessControlException
  {
    File file = new File(filename);
    String text = "";
    checkReadeable(file);
    Scanner scnr = new Scanner(file);

    while (scnr.hasNextLine())
    {
      if (text.isEmpty())
        text += scnr.nextLine();
      else
        text += "\n" + scnr.nextLine();
    }
    
    return text;
  }

  /**
   * Writes a given text to a File.
   *
   * @param text      Content of the File.
   * @param filename  Name for the file.
   */
  public static void writeToFile(String text, String filename)
  {
    Writer writer = null;

    try {
      FileOutputStream fos = new FileOutputStream(filename);
      OutputStreamWriter osw = new OutputStreamWriter(fos, "utf-8");
      writer = new BufferedWriter(osw);
      writer.write(text);
    } catch (IOException ex) 
    {
      System.out.println("Die Zieldatei konnte nicht geschrieben werden.");
    } finally 
    {
      try {
        writer.close();
      } catch (Exception ex) 
      {
        System.out.println("Die Zieldatei konnte nicht geschrieben werden.");
      }
    }
  }
}
