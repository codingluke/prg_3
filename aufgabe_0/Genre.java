import java.util.Random;
import java.util.Collections;
import java.util.Arrays;

/**
 * Enum-Klasse mit den Musik-Genres der CDs. 
 * Jedes Genre wird mit einem String initialisiert, die die
 * Ausgabe des Genres als String darstellt.
 * 
 * @author Lukas Hodel 
 *
 */
public enum Genre
{
	/** Genre Rock */
	ROCK("Rock"), 
	/** Genre Pop */
	POP("Pop"), 
	/** Genre Klassik */
	KLASSIK("Klassik"), 
	/** Genre HipHop */
	HIPHOP("HipHop"),
	/** Genre Metal */
  METAL("Metal"),
	/** Genre Techno */
  TECHNO("Techno"),
	/** Genre Jazz */
  JAZZ("Jazz");

  private String genre;
 
  /**
   * Cached die Werte in einen Array für Performance verbesserung.
   */
  private static final Genre[] VALUES = values();

  /** 
   * Cached die Grösse des Enums für Performance verbesserung.
   */
  private static final int SIZE = VALUES.length;
  
  /**
   * TODO : !!!
   */
  Genre(String genre)
  {
    this.genre = genre;
  }


  /**
   * Gibt ein zufälliges Genre zurück.
   *
   * @params random  Eine Random instanz.
   * 
	 * @return  ein zufälliges genre Genre.
   */
  public static Genre gibZufaellig(Random random)
  {
    return VALUES[random.nextInt(SIZE)];
  }
  
  /**
   * Überschreibt toString() damit der genre
   * Stringwert zurückgegeben wird.
   * 
	 * @return  Genre als String.
   */
  @Override
  public String toString()
  {
    return genre;
  }
}
