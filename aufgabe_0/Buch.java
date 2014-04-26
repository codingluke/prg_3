import java.util.Random;

/** 
 * Buch ist eine Unterklasse von Medium. Es ergänzt
 * Medium mit den für ein Buch benötigten Felder und Eigenschaften.
 *
 * @author Lukas Hodel
 *
 */
public class Buch extends Medium
{
  
  /**
   * Author des Buches.
   * @serial
   */
  private String author;
  
  /**
   * Handelt es sich um ein Hardcover oder nicht.
   * @serial
   */
  private boolean hardcover = true;

  /**
   * Der Konstruktor benoetigt alle Felder des Buches als Parameter
   *
   * @param titel   String Titel des Buches.
   * @param preis   Float Preis des Buches.
   * @param author  String Author des Buches.
   * @param hardcover boolean ob hardcover oder nicht.
   */
	public Buch(String titel, float preis, String author, boolean hardcover)
	{
    super(titel, preis);
    setzeAuthor(author);
    setzeHardcover(hardcover);
	}

  /**
   * Der Konstruktor benoetigt ein Random Objekt, dann
   * werden die Felder automatisch gefüllt.
   *
   * @param random  Objekt zur zufaelligen Wertegerierung.
   */
  public Buch(Random random)
  {
    super(random);
    setzeAuthor("Author " + random.nextInt(2000));
    setzeHardcover(random.nextBoolean());
  }

  public String gibAuthor()
  {
    return author;
  }
  
  /**
   * Setzt neuen Author des Buches.
   *
   * @param author  Neuer author.
   */
  public void setzeAuthor(String author)
  {
    this.author = author;
  }
  
  /**
   * Gibt zurueck ob es sich um ein Hardcover Buch handelt.
   */
  public boolean gibHardcover()
  {
    return hardcover;
  }
  
  /**
   * Setzt Buch als hardcover oder nicht.
   *
   * @param hardcover   Hardcover oder nicht.
   */
  public void setzeHardcover(boolean hardcover)
  {
    this.hardcover = hardcover;
  }
  
  /**
   * Definiert wie das Buch als String repraesentiert werden soll.
   *
   * Format: Buch 'Titel' von 'Author' [HARDCOVER]
   */
  @Override
  public String toString()
  {
    String beschreibung = "Buch '" + gibTitel() + "' von '" + gibAuthor() + "'";
    if (hardcover)
      beschreibung += " [HARDCOVER]";
    return beschreibung;
  }
}
