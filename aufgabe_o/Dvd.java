import java.util.Random;
/** 
 * Dvd ist eine Unterklasse von Medium. Es ergänzt
 * Medium mit den für eine CD benötigten Felder und Eigenschaften.
 *
 * @author Lukas Hodel
 *
 */
public class Dvd extends Medium
{
  
  /**
   * Regisseur des Filmes.
   * @serial
   */
  private String regisseur;
  
  /**
   * Alter ab welchem einen Film freigegeben wurde.
   * @serial
   */
  private int freigabealter;

  /**
   * Der Konstruktor benoetigt alle Felder des Buches als Parameter
   *
   * @param preis         float Preis der DVD.
   * @param regisseur     String Regisseur des Films.
   * @param freigabealter int Freigabealter für den Film.
   */
	public Dvd(String titel, float preis, String regisseur, int freigabealter)
	{
    super(titel, preis);
    setzeRegisseur(regisseur);
    setzeFreigabealter(freigabealter);
	}

  /**
   * Der Konstruktor benoetigt ein Random Objekt, dann
   * werden die Felder automatisch gefüllt.
   *
   * @param random  Objekt zur zufaelligen Wertegerierung.
   */
  public Dvd(Random random)
  {
    super(random);
    setzeTitel("Filmtitel " + random.nextInt(2000));
    setzeRegisseur("regisseur " + random.nextInt(2000));
    setzeFreigabealter(6 + random.nextInt(12));
  }

  /**
   * Gibt Regisseur der Cd zurueck.
   */
  public String gibRegisseur()
  {
    return regisseur;
  }
  
  /**
   * Setzt neuen Regisseur der Dvd.
   *
   * @param regisseur  neuer Regisseur.
   */
  public void setzeRegisseur(String regisseur)
  {
    this.regisseur = regisseur;
  }
  
  /**
   * Gibt Freigabealter zurueck.
   */
  public int gibfreigabealter()
  {
    return freigabealter;
  }
  
  /**
   * Setzt neues Freigabealter der Dvd.
   *
   * @param freigabealter   neues Freigabealter.
   */
  public void setzeFreigabealter(int freigabealter)
  {
    this.freigabealter = freigabealter;
  }
  
  /**
   * Definiert wie die Cd als String repraesentiert werden soll.
   *
   * Format: DVD 'Titel' von 'Regisseur' (frei ab freigabealter).
   */
  @Override
  public String toString()
  {
    return "DVD '" + gibTitel() + "' von '" + 
      gibRegisseur() + "' " + "(frei ab " + gibfreigabealter() + ")";
  }
}
