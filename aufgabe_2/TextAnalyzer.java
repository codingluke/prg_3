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
import java.io.FileReader;

public class TextAnalyzer
{
  /**
   * HashMap containing all words as key and its count as value.
   */
  private HashMap<String, Integer> wordCount;

  /**
   * Sorted and filtered HashMap. Contains just relevant words
   * as key and its count as value.
   */
  private HashMap<String, Integer> currentWordMap;

  /**
   * TextAnalyzer, filters the words out of a FileReader and
   * counts the occurence of the individual words.
   *
   * @param filename Name of the file to Analyze.
   */
  public TextAnalyzer(FileReader reader)
  {
    countWords(reader);
  }

  /**
   * Gives back the size of the actual wordlist.
   *
   * @return size of the actual wordlist.
   */
  public int currentSize()
  {
    return getCurrentWordMap().size();
  }

  /**
   * Sorts the wordlist by key, asc with no filter.
   */
  public void sort()
  {
    sort(true, true, 0, 0);
  }

  /**
   * Sorts the wordlist by key with no filter.
   *
   * @param asc   Direction true = asc, false = desc.
   */
  public void sort(boolean asc)
  {
    sort(true, asc, 0, 0);
  }

  /**
   * Sorts the wordlist by key, asc.
   *
   * @param min   Filter for min occurence of the word in the list.
   * @param max   Filter for max occurence of the word in the list.
   */
  public void sort(int min, int max)
  {
    sort(true, true, min, max);
  }

  /**
   * Sorts the wordlist by key.
   *
   * @param asc   Direction true = asc, false = desc.
   * @param min   Filter for min occurence of the word in the list.
   * @param max   Filter for max occurence of the word in the list.
   */
  public void sort(boolean asc, int min, int max)
  {
    sort(true, asc, min, max);
  }

  /**
   * Sorts the wordlist by values, asc, without filter.
   */
  public void sortByValues()
  {
    sort(false, true, 0, 0);
  }

  /**
   * Sorts the wordlist by values, without filter.
   *
   * @param asc   Direction true = asc, false = desc.
   */
  public void sortByValues(boolean asc)
  {
    sort(false, asc, 0, 0);
  }

  /**
   * Sorts the wordlist by value, asc.
   *
   * @param min   Filter for min occurence of the word in the list.
   * @param max   Filter for max occurence of the word in the list.
   */
  public void sortByValues(int min, int max)
  {
    sort(false, true, min, max);
  }

  /**
   * Sorts the wordlist by value (word occurence).
   *
   * @param asc   Direction true = asc, false = desc.
   * @param min   Filter for min occurence of the word in the list.
   * @param max   Filter for max occurence of the word in the list.
   */
  public void sortByValues(boolean asc, int min, int max)
  {
    sort(false, asc, min, max);
  }

  /**
   * Returns actual wordlist as a concatinated string.
   * Format: "word1                   1\nword2                   10\n"
   *
   * @return actual wordlist concatinated to one String.
   */
  @Override
  public String toString()
  {
    String result = "";
    Iterator it = getCurrentWordMap().entrySet().iterator();
    while (it.hasNext()) {
      Entry pairs = (Entry)it.next();
      String format = "%1$-25s%2$d%n";
      result += String.format(format, pairs.getKey(), pairs.getValue());
    }
    return result;
  }

  /**
   * Sorts and filters wordlist.
   *
   * @param byKey   Attribute to sort, true = byKey, false = byValue.
   * @param asc     Sortdirection true = asc, false = desc.
   * @param min     Filter for min occurence of the word in the list.
   * @param max     Filter for max occurence of the word in the list.
   */
  private void sort(boolean byKey, boolean asc, int min, int max)
  {
    currentWordMap = new LinkedHashMap<String, Integer>();
    LinkedList<String> sortedKeys = new LinkedList<String>();
    if (min > max)
    {
      int tmp = min;
      min = max;
      max = tmp;
    }
    if (byKey)
      sortedKeys = sortByKeys(wordCount, asc);
    else
      sortedKeys = sortByValues(wordCount, asc);
    for(String key: sortedKeys)
    {
      int count = wordCount.get(key);
      if ((min == 0 && max == 0) || (count >= min && count <= max))
        currentWordMap.put(key, count);
    }
  }

  /**
   * Sorts a Map by its keys and gives back the sorted keys as a
   * LinkedList.
   *
   * @param words The Map to be sorted.
   * @param asc   Direction to be sorted. true = asc, flase = desc.
   *
   * @return Sorted LinkedList containing the keys (words).
   */
  private LinkedList<String> sortByKeys(HashMap<String, Integer> words,
                                        final boolean asc)
  {
    LinkedList<String> keys = new LinkedList<String>(words.keySet());
    Collections.sort(keys, new Comparator<String>() {
      @Override
      public int compare(String key1, String key2) {
        int compare = 0;
        if (asc)
          compare = Collator.getInstance().compare(key1, key2);
        else
          compare = Collator.getInstance().compare(key2, key1);
        return compare;
      }
    });
    return keys;
  }

  /**
   * Sorts a Map by its value and gives back the sorted keys as a
   * LinkedList. Overrides method compare in the ananoumous class Comperator
   * used to define the sort direction.
   *
   * @param map   The Map to be sorted.
   * @param asc   Direction to be sorted. true = asc, flase = desc.
   *
   * @return Sorted LinkedList containing the keys (words).
   */
  private LinkedList<String> sortByValues(HashMap<String, Integer> words,
                                          final boolean asc)
  {
    LinkedList<Entry<String, Integer>> entries =
      new LinkedList<Entry<String, Integer>>(words.entrySet());
    Collections.sort(entries, new Comparator<Entry<String, Integer>>() {
      @Override
      public int compare(Entry<String, Integer> o1, Entry<String, Integer> o2)
      {
        int compare = 0;
        if (asc)
          compare = ((Integer)o1.getValue()).compareTo(o2.getValue());
        else
          compare = ((Integer)o2.getValue()).compareTo(o1.getValue());
        if (compare == 0)
          compare = Collator.getInstance().compare(
            (String)o1.getKey(), (String)o2.getKey());
        return compare;
      }
    });
    LinkedList<String> keys = new LinkedList<String>();
    for(Map.Entry<String, Integer> entry: entries)
      keys.add(entry.getKey());
    return keys;
  }

  /**
   * Returns current wordlist.
   *
   * @return current wordlist.
   */
  public HashMap<String, Integer> getCurrentWordMap()
  {
    HashMap<String, Integer> actualMap = currentWordMap;
    if (actualMap == null)
      actualMap = wordCount;
    return actualMap;
  }

  /**
   * Filters the words out of a FileReader and counts the occurence of the
   * individual word. A word is at least two chars long and contains no
   * special characters like (-,.«»§). Words are threated case-sensitive.
   *
   * @param reader  FileReader containing the textfile.
   */
  private void countWords(FileReader reader)
  {
    StreamTokenizer tokenizer = new StreamTokenizer(reader);
    tokenizer.ordinaryChars(',', '.');
    tokenizer.ordinaryChars('«', '»');
    tokenizer.ordinaryChars('§', '§');
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
          if (tokenizer.sval.length() > 1)
            wordCount.put(tokenizer.sval, count);
        }
      }
    }
    catch (IOException ex)
    {
      ex.printStackTrace();
    }
  }
}
