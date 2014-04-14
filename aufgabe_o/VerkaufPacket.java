/**
 * Buch ist eine Unterklasse von Medium. Es ergänzt
 * Medium mit den für ein Buch benötigten Felder und Eigenschaften.
 *
 * @author Lukas Hodel
 *
 */
public class VerkaufPacket implements Comparable<VerkaufPacket>
{
  /**
   * Tag des Verkaufs.
   * @serial
   */
  private Medium medium;
  
  /**
   * Welches Medium Verkauft wurde
   * @serial
   */
  private int anzahl;

  /**
   * Der Konstruktor benoetigt alle Felder des Buches als Parameter
   *
   * @param titel   String Titel des Buches.
   * @param preis   Float Preis des Buches.
   * @param author  String Author des Buches.
   * @param hardcover boolean ob hardcover oder nicht.
   */
	public VerkaufPacket(Medium medium, int anzahl)
	{
    setzeMedium(medium);
    setzeAnzahl(anzahl);
	}

  /**
   * Gibt Anzahl zurueck. Wie oft wurde das Medium verkauft.
   *
   * @return anzahl wie oft das Medium verkauft wurde.
   */
  public int gibAnzahl()
  {
    return anzahl;
  }
  
  /**
   * Setzt neue Anzahl an Medien.
   *
   * @param anzahl  neue Anzahl Medien im Packet.
   */
  public void setzeAnzahl(int anzahl)
  {
    this.anzahl = anzahl;
  }
  
  /**
   * Gibt verkauftes Medium zurueck.
   *
   * @return das verkaufte Medium.
   */
  public Medium gibMedium()
  {
    return medium;
  }
  
  /**
   * Setzt neues Medium welches Verkauft wurde.
   *
   * @param anzahl  neue Anzahl Medien im Packet.
   */
  public void setzeMedium(Medium medium)
  {
    this.medium = medium;
  }

  /**
   * Gibt verkaufspreis pro Medium zurueck.
   *
   * @return Einzelpreis des Mediums.
   */
  public float gibPreis()
  {
    return medium.gibPreis();
  }

  /**
   * Gibt der gesamte Verkaufspreis zurueck.
   *
   * @return der gesamte Preis. Anzahl * Preis.
   */
  public float gibGesamtPreis()
  {
    return Math.round(medium.gibPreis() * gibAnzahl() * 100) / 100.0f;
  }

  /**
   * Definiert die Gleichheit eines VerkaufPacket.
   *
   * @param obj  Objekt mit welchem verglichen wird.
   *
   * @return boolean ob gleich oder nicht.
   */
  @Override
  public boolean equals(Object obj)
  {
    VerkaufPacket gast = (VerkaufPacket) obj;

    if (obj == this)
      return true;
    else if (obj == null || obj.getClass() != this.getClass())
      return false;
 
    return medium.equals(gast.gibMedium());
  }

  /**
   * Ueberschreibt die Methode compareTo des interface Comparable.
   * Definiert die Sortierreihenfolge.
   *
   * @param gast  Das Gastobjekt mit welchem verglichen wird.
   *
   * @return Int  0 = gleich, 1 = groesser, -1 = kleiner
   */
  @Override
  public int compareTo(VerkaufPacket gast) {
    int vergleich = 0;

    if (this.gibGesamtPreis() == gast.gibGesamtPreis())
      vergleich = 0;
    else if ((this.gibGesamtPreis()) < gast.gibGesamtPreis())
      vergleich = 1;
    else
      vergleich = -1;

    return vergleich;
  }
}
