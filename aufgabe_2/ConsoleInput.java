import java.util.*;

/**
 * Class to read user input form the console.
 * There are methods to read strings, integers and doubles.
 * Integers and doubles can be read as intervals.
 *
 * @author Lukas Hodel
 */
public class ConsoleInput
{
  /** Objekt to capture console input. */
  private static Scanner scan = new Scanner(System.in);

  /**
   * Pivate constructor to prevent instances of this Class.
   */
  private ConsoleInput()
  {
  }

  /**
   * Reads Stringinput form the console and gives it back.
   *
   * @return		Readed String.
   */
  public static String readString()
  {
    return readString("");
  }

  /**
   * Prints an infotext for the user, reads input as string and
   * returns it.
   *
   * @param info		Information fuer den Benutzer.
   *
   * @return		Readed String.
   */
  public static String readString(String info)
  {
    System.out.print(info);
    String text = "";
    boolean isOk = false;
    while (!isOk)
    {
      text = scan.next();
      if (text != null)
      isOk = true;
    }
    return text;
  }

  /**
   * Reads an integer value from the console and returns it.
   *
   * @return		Readed Integer.
   */
  public static int readInt()
  {
    return readInt("");
  }

  /**
   * Prints an information for the user, reads a string from the console
   * and tryes to convert the string into an Integer. If there is a
   * parse error, the user gets informed by an errortext and prompted
   * to enter a valid number again. As soon the convertion is
   * successfull, the integer gets returned.
   *
   * @param info		Information to the user.
   *
   * @return		    Readed String.
   */
  public static int readInt(String info)
  {
    int value = 0;
    boolean isOk = false;
    while (!isOk)
    {
      try
      {
        value = Integer.parseInt(readString(info));
        isOk = true;
      }
      catch (NumberFormatException nfe)
      {
        System.out.println("Eine ganze Zahl eingeben.");
      }
    }
    return value;
  }

  /**
   * Reads an integer in between an interval from the console and returns it.
   *
   * @param min		Interval top bound.
   * @param max		Interval lower bound.
   *
   * @return		  Readed integer from the interval.
   */
  public static int readInt(int min, int max)
  {
    return readInt("", min, max);
  }

  /**
   * Prints an information to the user, reads an integer in between
   * an given interval and returns it. Is the Integer not between the
   * given interval, an errormessage is displayed and the user gets prompted
   * to enter a new integer until there is a valid input.
   *
   * @param info	Information to the user.
   * @param min		Interval top bound.
   * @param max		Interval lower bound.
   *
   * @return		  Readed integer from the given interval.
   */
  public static int readInt(String info, int min, int max)
  {
    int value = readInt(info);
    while (value < min || value > max)
    {
      System.out.printf("Eine Zahl zwischen %d und %d eingeben!\n", min, max);
      value = readInt(info);
    }
    return value;
  }

  /**
   * Reads a string from the console converted to a floating-point number.
   *
   * @return		Readed floating-point number.
   */
  public static double readDouble()
  {
    return readDouble("");
  }

  /**
   * Prints an information to the console and reads a string converted
   * to a floating-point number. If there is a convertion error, the user
   * gets prompted to reenter a valid floating-point.
   *
   * @param info		Information to the user.
   *
   * @return		Readed floating-point number as double.
   */
  public static double readDouble(String info)
  {
    double value = 0.0;
    boolean isOk = false;
    while (!isOk)
    {
      try
      {
        value = Double.parseDouble(readString(info));
        isOk = true;
      }
      catch (NumberFormatException nfe)
      {
        System.out.print("Eine Zahl eingeben.\t");
      }
    }
    return value;
  }

  /**
   * Reads a string from the console, converted into a floating-point number
   * in between a given interval and returns it.
   *
   * @param min		Interval top bound.
   * @param max		Interval lower bound.
   *
   * @return		Readed floating-point number in the interval.
   */
  public static double readDouble(double min, double max)
  {
    return readDouble("", min, max);
  }

  /**
   * Prints an information to the user and reads a floating-point number in
   * between a certain interval from the console. If the input is not a
   * number or the number is not in between the interval, it returns an
   * error and prompts the user to reenter a correct value. As soon as
   * the input value is valid the floating-point number gets returned.
   *
   * @param info	Infotext for the user.
   * @param min		Interval top bound.
   * @param max		Interval lower bound.
   *
   * @return		  Readed floating-point in a certain interval from the console.
   */
  public static double readDouble(String info, double min, double max)
  {
    double value = readDouble(info);
    while (value < min || value > max)
    {
      System.out.printf("Eine Zahl zwischen %.15f und %.15f eingeben!\n",
                        min, max);
      value = readDouble(info);
    }
    return value;
  }
}
