import java.io.StreamTokenizer;
import java.io.StringReader;
import java.io.IOException;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;
import java.util.Map.Entry;
import java.util.NavigableSet;
import java.util.TreeSet;
import java.util.LinkedList;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Comparator;
import java.util.Collections;

public class TextAnalyzer
{
  private StreamTokenizer tokenizer;
  private HashMap<String, Integer> wordCount;

  public TextAnalyzer(String text)
  {
    StringReader reader = new StringReader(text);
    tokenizer = new StreamTokenizer(reader);
    countWords();
  }

  public void printByKey()
  {
    printByKey(true, 0, 0);
  }

  public void printByKey(boolean asc)
  {
    printByKey(asc, 0, 0);
  }

  public void printByKey(int min, int max)
  {
    printByKey(true, min, max);
  }

  public void printByKey(boolean asc, int min, int max)
  {
    if (min > max)
    {
      int tmp = min;
      min = max;
      max = min;
    }
    Iterator<String> iterator = getIteratorSortedByKey(asc);
    while (iterator.hasNext()) {
      String word = iterator.next();
      int count = wordCount.get(word);
      if ((min == 0 && max == 0) || (count >= min && count <= max))
        System.out.println(word + "   " + wordCount.get(word));
    }
  }

  private Iterator<String> getIteratorSortedByKey(boolean asc)
  {
    NavigableSet<String> sortedSet = new TreeSet<String>(wordCount.keySet());
    Iterator<String> iterator;
    if (asc)
      iterator = sortedSet.iterator();
    else
      iterator = sortedSet.descendingIterator();
    return iterator;
  }

  /*
   * Paramterized method to sort Map e.g. HashMap or Hashtable in Java
   * throw NullPointerException if Map contains null key
   */
  public static <K extends Comparable,V extends Comparable> Map<K,V>
                sortByKeys(Map<K,V> map)
  {
      List<K> keys = new LinkedList<K>(map.keySet());
      Collections.sort(keys);
      Map<K,V> sortedMap = new LinkedHashMap<K,V>();
      for(K key: keys){
          sortedMap.put(key, map.get(key));
      }
      return sortedMap;
  }

  /*
   * Java method to sort Map in Java by value e.g. HashMap or Hashtable
   * throw NullPointerException if Map contains null values
   * It also sort values even if they are duplicates
   */
  public static <K extends Comparable,V extends Comparable> Map<K,V>
                sortByValues(Map<K,V> map)
  {
    List<Map.Entry<K,V>> entries = new LinkedList<Map.Entry<K,V>>(map.entrySet());
    Collections.sort(entries, new Comparator<Map.Entry<K,V>>() {
      @Override
      public int compare(Entry<K, V> o1, Entry<K, V> o2) {
          return o1.getValue().compareTo(o2.getValue());
      }
    });
    Map<K,V> sortedMap = new LinkedHashMap<K,V>();
    for(Map.Entry<K,V> entry: entries){
        sortedMap.put(entry.getKey(), entry.getValue());
    }
    return sortedMap;
  }

  private void countWords()
  {
    wordCount = new HashMap<String, Integer>();
    try
    {
      while(tokenizer.nextToken() != StreamTokenizer.TT_EOF)
      {
        if (tokenizer.ttype == StreamTokenizer.TT_WORD)
        {
          int count = 1;
          if (wordCount.containsKey(tokenizer.sval))
            count = wordCount.get(tokenizer.sval) + 1;
          wordCount.put(tokenizer.sval, count);
        }
        else if(tokenizer.ttype == StreamTokenizer.TT_NUMBER)
        {
          System.out.println(tokenizer.nval);
        }
        else if(tokenizer.ttype == StreamTokenizer.TT_EOL)
        {
            System.out.println();
        }
      }
    }
    catch (IOException ex)
    {
      ex.printStackTrace();
    }
  }
}
