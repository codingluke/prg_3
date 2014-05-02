import java.io.FileOutputStream;
import java.io.IOException;
import java.io.File;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.nio.file.Path;
import java.nio.file.FileAlreadyExistsException;
import java.io.FileNotFoundException;
import java.io.BufferedWriter;
import java.io.Writer;
import java.io.OutputStreamWriter;
import java.security.AccessControlException;
import java.util.Scanner;
import java.util.InputMismatchException;

public class FileController
{
	/**
   * Private constructor to prevent instances of this Class.
   */
  private FileController()
  {
  }

  /**
   * Checks if a file exists according its name.
   *
   * @param filename  Name of the file to check.
   *
   * @return boolean if file exists or not.
   */
  public static boolean fileExists (String filename)
  {
    File file = new File(filename);
    return file.isFile();
  }

  /**
   * Creates a new File. Checks if file already exists.
   * Asks if file should be overwridden.
   *
   * @param filename  Filename for the new file.
   *
   * @throws FileAlreadyExistsException
   */
  public static void createFile (String filename)
    throws FileAlreadyExistsException
  {
    Path target = Paths.get(filename);
    try
    {
      Files.createFile(target);
    }
    catch (FileAlreadyExistsException e) {
      askToOverrideExistingFile(e.getMessage());
    }
    catch (IOException e) {
      System.out.println(e.getMessage());
    }
  }

  /**
   * Prompts the user to allow the file to be overwridden or
   * throws a FileNotFoundException.
   *
   * @param filename  Name of the already existed file.
   */
  private static void askToOverrideExistingFile (String filename)
    throws FileAlreadyExistsException
  {
    System.out.println("Achtung: Datei " + filename + " ist schon vorhanden!");
    System.out.print("  Uebeschreiben? (j/n): ");
    if (readYesOrNo().equals("n"))
      throw new FileAlreadyExistsException(filename);
  }

  /**
   * Reads from terminal and ensures that the input is 'y' or 'n'.
   *
   * @return String y or n
   */
  private static String readYesOrNo()
  {
    String input = "";
    Scanner scanner = new Scanner(System.in);
    try
    {
      input = scanner.next("j|n");
    }
    catch (InputMismatchException e)
    {
      System.out.print("Es sind nur die Zeichen 'j' und 'n' erlaubt!: ");
      input = readYesOrNo();
    }
    return input;
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
      throw new FileNotFoundException(file.getName());
    else if (!file.canRead())
      throw new AccessControlException(file.getName());
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
    }
    catch (IOException e)
    {
      System.out.println("Die Datei " + e.getMessage()
        + "konnte nicht geschrieben werden.");
    }
    finally
    {
      try {
        writer.close();
      }
      catch (Exception e)
      {
        System.out.println("Die Datei " + e.getMessage()
          + "konnte nicht geschrieben werden.");
      }
    }
  }
}
