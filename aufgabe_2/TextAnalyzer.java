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
import java.text.Collator;

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
    List<String> sortedWords = sortByKeys(wordCount, asc);
    for(String word: sortedWords)
    {
      int count = wordCount.get(word);
      if ((min == 0 && max == 0) || (count >= min && count <= max))
        System.out.println(word + "   " + wordCount.get(word));
    }
  }

  public void printByValue(boolean asc, int min, int max)
  {
    if (min > max)
    {
      int tmp = min;
      min = max;
      max = min;
    }
    List<String> sortedWords = sortByValues(wordCount, asc);
    for(String word: sortedWords)
    {
      int count = wordCount.get(word);
      if ((min == 0 && max == 0) || (count >= min && count <= max))
        System.out.println(word + "   " + wordCount.get(word));
    }
  }

  /*
   * Paramterized method to sort Map e.g. HashMap or Hashtable in Java
   * throw NullPointerException if Map contains null key
   */
  private LinkedList<String> sortByKeys(Map<String, Integer> map, boolean asc)
  {
    LinkedList<String> keys = new LinkedList<String>(map.keySet());
    if (asc)
    {
      Collections.sort(keys, new Comparator<String>() {
        @Override
        public int compare(String key1, String key2) {
          return Collator.getInstance().compare(key1, key2);
        }
      });
    }
    else
    {
      Collections.sort(keys, new Comparator<String>() {
        @Override
        public int compare(String key1, String key2) {
          return Collator.getInstance().compare(key2, key1);
        }
      });
    }
    return keys;
  }

  /*
   * Java method to sort Map in Java by value e.g. HashMap or Hashtable
   * throw NullPointerException if Map contains null values
   * It also sort values even if they are duplicates
   */
  private LinkedList<String> sortByValues(Map<String, Integer> map, boolean asc)
  {
    LinkedList<Map.Entry<String, Integer>> entries = new LinkedList<Map.Entry<String, Integer>>(map.entrySet());
    if (asc)
    {
      Collections.sort(entries, new Comparator<Map.Entry<String, Integer>>() {
        @Override
        public int compare(Entry<String, Integer> o1, Entry<String, Integer> o2) {
          return ((Integer)o1.getValue()).compareTo(o2.getValue());
        }
      });
    }
    else
    {
      Collections.sort(entries, new Comparator<Map.Entry<String, Integer>>() {
        @Override
        public int compare(Entry<String, Integer> o1, Entry<String, Integer> o2) {
          return ((Integer)o2.getValue()).compareTo(o1.getValue());
        }
      });
    }
    LinkedList<String> keys = new LinkedList<String>();
    for(Map.Entry<String, Integer> entry: entries){
      keys.add(entry.getKey());
    }
    return keys;
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
        //else if(tokenizer.ttype == StreamTokenizer.TT_NUMBER)
        //{
          //System.out.println(tokenizer.nval);
        //}
        //else if(tokenizer.ttype == StreamTokenizer.TT_EOL)
        //{
            //System.out.println();
        //}
      }
    }
    catch (IOException ex)
    {
      ex.printStackTrace();
    }
  }
}
