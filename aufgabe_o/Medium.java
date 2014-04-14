import java.io.Serializable;
import java.util.Random;
import java.util.*;

/** 
 * Basisklasse für Mediumobjekte. Darin werden die von allen untertypen
 * verwendeten Attributte definiert. Auch die Serialisierungsmethode
 * wird hier definiert.
 *
 * @author Lukas Hodel
 *
 */
public abstract class Medium implements Serializable
{
  private static final long serialVersionUID = 7526472295622776147L;

  /**
   * Titel des Mediums
   * @serial
   */
  private String titel;
  
  /**
   * Preis des Mediums, als float da Kommastellen benötigt.
   * @serial
   */
  private float preis;

  /**
   * Der Konstruktor benoetigt alle Felder des Mediums als Parameter
   *
   * @param titel   Titel des Mediums.
   * @param preis   Preis des Mediums.
   */
	public Medium(String titel, float preis)
	{
    setzeTitel(titel);
    setzePreis(preis);
	}

  /**
   * Der Konstruktor benoetigt ein Random Objekt, dann
   * werden die Felder automatisch gefüllt.
   *
   * @param random  Objekt zur zufaelligen Wertegerierung.
   */
  public Medium(Random random)
  {
    float minX = 50.0f;
    float maxX = 100.0f;
    float zufallsPreis = random.nextFloat() * (maxX - minX) + minX;

    setzeTitel("Titel " + random.nextInt(2000));
    setzePreis(zufallsPreis);
  }

  /**
   * Gibt den Titel zurueck.
   */
  public String gibTitel()
  {
    return titel;
  }
  
  /**
   * Setzt den Ttitel.
   * 
   * @param titel   neuer Titel.
   */
  public void setzeTitel(String titel)
  {
    this.titel = titel;
  }
  
  /**
   * Gibt den Preis zurueck.
   */
  public float gibPreis()
  {
    return preis;
  }
  
  /**
   * Setzt den Preis neu.
   * 
   * @param preis   neuer Preis.
   */
  public void setzePreis(float preis)
  {
    this.preis = Math.round(preis* 100) / 100.0f;
  }

  /**
   * Ueberschreibt die equals funktion so, dass ein
   * Medium gleich ist, wenn der Titel, der Preis
   * und die Klasse identisch sind.
   */
  @Override
  public boolean equals(Object obj)
  {
    Medium gast = (Medium) obj;

    if (obj == this)
      return true;
    if (obj == null || obj.getClass() != this.getClass())
      return false;
 
    return gibTitel().equals(gast.gibTitel()) 
      && gibPreis() == gast.gibPreis();
  }
}
