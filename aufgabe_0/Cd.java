import java.util.Random;
/** 
 * Cd ist eine Unterklasse von Medium. Es ergänzt
 * Medium mit den für eine CD benötigten Felder und Eigenschaften.
 *
 * @author Lukas Hodel
 *
 */
public class Cd extends Medium
{
  
  /**
   * Interpret der Cd.
   * @serial
   */
  private String interpret;
  
  /**
   * Musikalisches Genre der Cd.
   * @serial
   */
  private Genre genre;

  /**
   * Der Konstruktor benoetigt alle Felder des Buches als Parameter
   *
   * @param titel     String Titel der CD.
   * @param preis     float Preis der CD.
   * @param interpret String Interpret der CD.
   * @param genre     genre der CD als Enum Genre.
   */
	public Cd(String titel, float preis, String interpret, Genre genre)
	{
    super(titel, preis);
    setzeInterpret(interpret);
    setzeGenre(genre);
	}

  /**
   * Der Konstruktor benoetigt ein Random Objekt, dann
   * werden die Felder automatisch gefüllt.
   *
   * @param random  Objekt zur zufaelligen Wertegerierung.
   */
  public Cd(Random random)
  {
    super(random);
    setzeTitel("Cd Titel " + random.nextInt(2000));
    setzeInterpret("Interpret " + random.nextInt(2000));
    setzeGenre(Genre.gibZufaellig(random));
  }

  /**
   * Gibt Interpret der Cd zurueck.
   */
  public String gibInterpret()
  {
    return interpret;
  }
  
  /**
   * Setzt neuer Interpret.
   *
   * @param interpret  neuer Interpret.
   */
  public void setzeInterpret(String interpret)
  {
    this.interpret = interpret;
  }
  
  /**
   * Gibt Genre der Cd zurueck.
   */
  public Genre gibGenre()
  {
    return genre;
  }
  
  /**
   * Setzt neues Genre der Cd.
   *
   * @param genre   Genre der Cd.
   */
  public void setzeGenre(Genre genre)
  {
    this.genre = genre;
  }

  /**
   * Definiert wie die Cd als String repraesentiert werden soll.
   *
   * Format: CD 'Titel' von 'Interpret' [genre]
   */
  @Override
  public String toString()
  {
    return "CD '" + gibTitel() + "' von '" + 
      interpret + "' " + "[" + genre.toString() + "]";
  }
}
