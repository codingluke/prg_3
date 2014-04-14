import java.io.Serializable;

/** 
 * Buch ist eine Unterklasse von Medium. Es ergänzt
 * Medium mit den für ein Buch benötigten Felder und Eigenschaften.
 *
 * @author Lukas Hodel
 *
 */
public class Verkauf implements Serializable
{
  
  /**
   * Tag des Verkaufs.
   * @serial
   */
  private int tag;

  /**
   * Wie oft wurde das Medium verkauft.
   * @serial
   */
  private int anzahl;
  
  /**
   * Welches Medium Verkauft wurde
   * @serial
   */
  private Medium medium;


  /**
   * Anzahl wie oft das Medium an dem Tag verkauft wurde
   * @serial
   */
  //private int anzahl;

  /**
   * Der Konstruktor benoetigt alle Felder des Verkaufs.
   *
   * @param tag     Tag an welchem verkauft wurde.
   * @param medium  das verkaufte Medium.
   * @param anzahl  die anzahl, wie oft das Medium verkauft wurde.
   */
	public Verkauf(int tag, Medium medium, int anzahl)
	{
    setzeTag(tag);
    setzeMedium(medium);
    setzeAnzahl(anzahl);
	}

  /**
   * Gibt den Verkaufstag zurueck.
   */
  public int gibTag()
  {
    return tag;
  }
  
  /**
   * Setze den Tag an welchem das Medium verkauft wurde.
   *
   * @param tag   verkaufstag.
   */
  public void setzeTag(int tag)
  {
    this.tag = tag;
  }
  
  /**
   * Gibt das Medium zurueck welches verkauft wurde.
   */
  public Medium gibMedium()
  {
    return medium;
  }
  
  /**
   * Setze das verkaufte Medium
   *
   * @param anzahl  Anzahl wie oft das Medium verkauft wurde.
   */
  public void setzeMedium(Medium medium)
  {
    this.medium = medium;
  }
  
  /**
   * Gibt die Anzahl zurueck wie oft das Medium verkauft wurde.
   */
  public int gibAnzahl()
  {
    return anzahl;
  }
  
  /**
   * Setze die anzahl des Verkaufs.
   *
   * @param anzahl  Anzahl wie oft das Medium verkauft wurde.
   */
  public void setzeAnzahl(int anzahl)
  {
    this.anzahl = anzahl;
  }
}
