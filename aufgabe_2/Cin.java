import java.util.*;

/**
 * Einfache Klasse zum einlesen von Konsoleneingaben.
 * Kann Strings, Integer und Double einlesen.
 * Integer und Double koennen auch aus Intervallen eingelesen werden.
 *
 * @author borstie
 *
 */
public class Cin
{
	/** Objekt zum erfassen von Konsoleneingaben */
	private static Scanner scan = new Scanner(System.in);

	/**
	 * Privater Konstrukter, um zu verhindern, dass Objekte von der
	 * Klasse erstellt werden koennen.
	 */
	private Cin()
	{
	}

	/**
	 * Liest eine Konsoleneingabe als Zeichenkette ein und gibt diese zurueck.
	 *
	 * @return		Readed String.
	 */
	public static String readString()
	{
		return readString("");
	}

	/**
	 * Gibt eine Information fuer den Benutzer aus, und liest anschliessend
	 * eine Konsoleneingabe als Zeichenkette ein und gibt diese zurueck.
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
	 * Liest einen Integerwert von der Konsole ein und gibt diesen zurueck.
	 *
	 * @return		Readed String.
	 */
	public static int readInt()
	{
		return readInt("");
	}

	/**
	 * Gibt eine Information fuer den Benutzer aus und liest anschliessend
	 * eine Zeichenkette von der Konsole ein und versucht diese in einen
	 * Integer umzuwandeln. Geht das nicht wird eine Fehlermeldung
	 * ausgegeben und der Benutzer zu einer erneuten Eingabe aufgefordert,
	 * sonst wird der Integerwert zurueck gegebenen.
	 *
	 * @param info		Information fuer den Benutzer.
	 *
	 * @return		Readed String.
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
	        	System.out.print("Eine ganze Zahl eingeben.\t");
			}
		}
		return value;
	}

	/**
	 * Liest einen Integerwert aus einem bestimmten Intervall und gibt diesen
	 * zurueck.
	 *
	 * @param min		Intervalluntergrenze
	 * @param max		Intervallobergrenze
	 *
	 * @return		  Readed integer from the interval.
	 */
	public static int readInt(int min, int max)
	{
		return readInt("", min, max);
	}

	/**
	 * Gibt eine Information fuer den Benutzer aus und liest anschliessend
	 * einen Integerwert aus einem bestimmten Intervall ein und gibt diesen
	 * zurueck. Liegt der eingegebene Wert nicht im Intervall, so wird eine
	 * Fehlermeldung ausgegeben und der Benutzer zu einer erneuten Eingabe
	 * aufgefordert.
	 *
	 * @param info	Information fuer den Benutzer
	 * @param min		Intervalluntergrenze
	 * @param max		Intervallobergrenze
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
	 * Liest eine Konsoleneingabe als Zeichenkette ein und ueberprueft,
	 * ob es sich um einen Gleitkommawert handelt. Sollte es sich nicht
	 * um einen Gleitkommawert handeln, wird eine Fehlermeldung ausgegeben
	 * und der Benutzer zu einer erneuten Eingabe aufgefordert.
	 *
	 * @return		Eingelesener Gleitkommawert.
	 */
	public static double readDouble()
	{
		return readDouble("");
	}

	/**
	 * Gibt eine Information fuer den Benutzer aus und liest anschliessend
	 * einen Gleitkommawert ein und gibt diesen zurueck.
	 *
	 * @param info		Information fuer den Benutzer.
	 *
	 * @return		Eingelesener Gleitkommawert.
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
	 * Liest einen Gleitkommawert aus einem bestimmten Intervall ein und gibt
	 * diesen zurueck.
	 *
	 * @param min		Intervalluntergrenze
	 * @param max		Intervallobergrenze
	 *
	 * @return		Eingelesener Gleitkommawert aus dem angegebenen Intervall.
	 */
	public static double readDouble(double min, double max)
	{
		return readDouble("", min, max);
	}

	/**
	 * Gibt eine Information fuer den Benutzer aus und liest anschliessend
	 * einen Gleitkommawert aus einem bestimmten Intervall ein und gibt diesen
	 * zurueck. Liegt der eingegebene Wert nicht im Intervall, so wird eine
	 * Fehlermeldung ausgegeben und der Benutzer zu einer erneuten Eingabe
	 * aufgefordert.
	 *
	 * @param info			Information fuer den Benutzer
	 * @param min			Intervalluntergrenze
	 * @param max			Intervallobergrenze
	 *
	 * @return		Eingelesener Gleitkommawert aus dem angegebenen Intervall.
	 */
	public static double readDouble(String info, double min, double max)
	{
		double value = readDouble(info);
		while (value < min || value > max)
		{
			System.out.printf("Eine Zahl zwischen %.15f und %.15f eingeben!\n", min, max);
			value = readDouble(info);
		}
		return value;
	}
}
