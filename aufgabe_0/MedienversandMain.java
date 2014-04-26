import java.util.Random;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.util.ArrayList;
import java.util.Collections;

/**
 * Simulation eines Medienversands der Buecher, CDs und DVDs vertreibt.
 * Es werden fuer 365 Tage eine vom Benutzer gewuenschte Anzahl Medien zufaellig
 * generiert und in die Dateien Medien.dat und Verkauf.dat geschrieben.
 * Es kann danach fuer einen beliebigen Tag die Verkaufsdaten ausgegeben werden.
 * Es handelt sich um ein Terminal Programm.
 *
 * @author Lukas Hodel
 *
 */
public class MedienversandMain 
{

  /**
   * Name des Programmes.
   */
  public final static String NAME = "MedienversandMain";

  /** 
   * Ein Random Objekt um zufällig ein Enum auszugeben.
   * Es ist wichtig immer nur ein Objekt zu erstellen, damit
   * die Zufälligkeit auch richtig funktioniert.
   */
  private static final Random RANDOM = new Random();

	/**
	 * Konstruktor um zu verhindern, das von dieser Klasse kein Objekt erzeugt
	 * werden kann.
	 */
	private MedienversandMain()
	{
	}
	
	/**
	 * Ueberprueft die uebergebenen Parameter und startet die Simulation, wenn
	 * die Paramter ok sind. Sonst wird eine Information ausgegeben, wie das
	 * Programm zu Benutzen ist.
	 *
	 * @param args		Fuer die Simulation benoetigten Programmparameter.
	 */
	public static void main(String[] args)
	{
    if (args.length == 2) 
    {
      if (args[0].equals("generiere"))
      {
        int anzahl = versucheInIntZuWandeln(args[1]);
        ArrayList<Medium> medien = generiereMedienobjekte(anzahl);
        ArrayList<Verkauf> verkaeufe = simuliereVerkaufsjahr(medien);
        speichereObjekt(medien, "Medien.dat");
        speichereObjekt(verkaeufe, "Verkauf.dat");
      }
      else if (args[0].equals("zeige"))
      {
        int tag = versucheInIntZuWandeln(args[1]);
        zeigeVerkaufstag(tag);
      }
      else
        schreibeBenutzungsInfo();
    }
		else
      schreibeBenutzungsInfo();
	}

  /**
   * Generiert eine Anzahl zufaelliger Medienobjekte.
   *
   * @param anzahl  Anzahl Medienobjekte die generiert werden sollen.
   *
   * @return Liste von Medien vom Typ Cd, Dvd oder Buch.
   */
  private static ArrayList<Medium> generiereMedienobjekte(int anzahl)
  {
		System.out.println("Generiere " + anzahl + " Medienobjekte");
    ArrayList<Medium> medien = new ArrayList<Medium>();
    for(int i = 0; i < anzahl; i++)
    {
      switch(RANDOM.nextInt(3)) {
        case 0:
          medien.add(new Buch(RANDOM));
          break;
        case 1:
          medien.add(new Cd(RANDOM));
          break;
        case 2:
          medien.add(new Dvd(RANDOM));
      }
    }
    return medien;
  }

  /**
   * Simuliert ein Verkaufsjahr. Es wird fuer jeden Tag im Jarh zwischen
   * 50 und 300 Bestellungen zufaelliger Medien gemacht. Pro Bestellung
   * koennen 1 bis 10 des selben Mediums bestellt werden.
   *
   * @param medien  Liste von Medien welche bestellt werden koennen.
   *
   * @return Liste von verkaufsinformationen.
   */
  private static ArrayList<Verkauf> simuliereVerkaufsjahr(ArrayList<Medium> medien)
  {
		System.out.println("Simuliere Verkaufsjahr");
    int anzahlMedien = medien.size();
    ArrayList<Verkauf> verkaeufe = new ArrayList<Verkauf>();

    // Fuer jeden Tag eines Jahres
    for (int tag = 1; tag <= 365; tag++)
    {
      // Zwischen 50 und 300 verkaeufe
      int anzVerkaeufe = 50 + RANDOM.nextInt(250);
      for (int i = 1; i <= anzVerkaeufe; i++)
      {
        Medium medium = medien.get(RANDOM.nextInt(anzahlMedien));

        Verkauf verkauf = new Verkauf(tag, medium, 1 + RANDOM.nextInt(9));
        verkaeufe.add(verkauf);
      }
    }
    return verkaeufe;
  }

  /**
   * Speichert das uebergebene Objekt in eine Datei.
   *
   * @param obj         zu speicherndes Objekt.
   * @param dateiname   Name der Datei die geschrieben wird.
   */
  private static void speichereObjekt(Object obj, String dateiname)
  {
    FileOutputStream fos = null;
    ObjectOutputStream out = null;

    try 
    {
      fos = new FileOutputStream(dateiname);
      out = new ObjectOutputStream(fos);
      out.writeObject(obj);
      out.close();
      System.out.println(dateiname + " geschrieben!");
    }
    catch (IOException ex)
    {
      ex.printStackTrace();
    }
  }

  /**
   * Liest eine Datei beliebigen types ein.
   *
   * @param dateiname   Name der Datei welche ausgelesen werden soll.
   *
   * @return Gere
   */
  @SuppressWarnings("unchecked")
  private static <T> T leseListe(String dateiname)
  {
    T liste = null;
    try
    {
       FileInputStream fileIn = new FileInputStream(dateiname);
       ObjectInputStream in = new ObjectInputStream(fileIn);
       liste = (T) in.readObject();
       in.close();
       fileIn.close();
    } catch(IOException i)
    {
       i.printStackTrace();
    } catch(ClassNotFoundException c)
    {
       System.out.println("class not found");
       c.printStackTrace();
    }
    return liste;
  }
  
  /**
   * Gibt die Verkaufsdaten eines spezifischen Tages im Jahr aus.
   *
   * @param tag     Int Wert als gewuenschter Tag im Jahr.
   */
  private static void zeigeVerkaufstag(int tag)
  {
    ArrayList verkaeufe = leseListe("Verkauf.dat");
    ArrayList<VerkaufPacket> tagesVerkaeufe = summiereTagesverkaeufe(verkaeufe, tag);
    System.out.println("Verkaufsuebersicht fuer den " + tag + " Tag");
    System.out.println("===================================");
    Collections.sort(tagesVerkaeufe);
    int index = 1;
    for (VerkaufPacket packet : tagesVerkaeufe) {
      Medium medium = packet.gibMedium();
      String format = "%2d) %2$-60s:   %3$-15s  %4$-15s %n";
      System.out.format(format, index, medium.toString(), 
                        packet.gibAnzahl() + " * " + packet.gibPreis() + " EUR =", 
                        packet.gibGesamtPreis() + " EUR");
      index++;
    }
  }

  /**
   * Filter die ArrayListe verkaeufe nach dem Tag und summiert
   * den Preis gleicher Medien auf.
   *
   * @param verkaeufe   Liste mit allen verkauefen.
   *
   * @return liste mit VerkaufPackete, die Verkaeufe aufsummiert 
   */
  private static ArrayList<VerkaufPacket> summiereTagesverkaeufe(ArrayList verkaeufe, int tag)
  {
    ArrayList<VerkaufPacket> tagesVerkaeufe = new ArrayList<VerkaufPacket>();
    for (Object v : verkaeufe) {
      Verkauf verkauf = (Verkauf) v;
      if (verkauf.gibTag() == tag)
      {
        VerkaufPacket verkauftesMedium = new VerkaufPacket(verkauf.gibMedium(), verkauf.gibAnzahl());
        if (tagesVerkaeufe.contains(verkauftesMedium))
        {
          int index = tagesVerkaeufe.indexOf(verkauftesMedium);
          VerkaufPacket schonVorhandenesMedium = tagesVerkaeufe.get(index);
          schonVorhandenesMedium.setzeAnzahl(verkauftesMedium.gibAnzahl() + schonVorhandenesMedium.gibAnzahl());
        }
        else
          tagesVerkaeufe.add(verkauftesMedium);
      }
    }
    return tagesVerkaeufe;
  }
	
	/**
   * Gibt Infos zur Benutzung des Programms aus.
	 */
	private static void schreibeBenutzungsInfo()
	{
		System.out.println("Benutzungsinfo fuer den Medienversand Simulator");
		System.out.println("\nEs gibt 2 moegliche Aufrufe:");
		System.out.println("\n1) java " + NAME + " generiere n");
		System.out.println("2) java " + NAME + " zeige t\n");
		System.out.println("mit 1 < n <= 1000 und t = 365\n");
		System.out.println("n ist die Anzahl der zu erzeugenden Mediendaten.");
		System.out.println("t ist die Anzahl der Tage, fuer die der Medienversand simuliert wird.");
		System.out.println("t kann nicht selbst bestimmt werden und ist festgesetzt auf 365 Tage.");
	}
	
	/**
	 * Ueberprueft ob ein String in ein Integer umgewandelt werden kann. Geht
   * das nicht, wird die Benutzungsinfo fuer das Programm ausgegeben.
	 *
	 * @param wert			String der in einen Integer umgewandelt werden soll.
	 * 
	 * @return          Der aus einem String umgewandelte Integerwert.
	 */
	private static int versucheInIntZuWandeln(String wert)
	{
		int wertInInt = 0;
		try
		{
			wertInInt = Integer.parseInt(wert);
		} catch (NumberFormatException nfe)
		{
			schreibeBenutzungsInfo();
		}
		return wertInInt;
	}
}

