import java.io.StreamTokenizer;
import java.io.StringReader;
import java.io.IOException;

public class TextAnalyzer
{
  private StreamTokenizer tokenizer;

  public TextAnalyzer(String text)
  {
    StringReader reader = new StringReader(text);
    tokenizer = new StreamTokenizer(reader);
  }

  public void analyze()
  {
    //Map<String, int> wordCount = new HashMap<String, int>();
    try
    {
      while(tokenizer.nextToken() != StreamTokenizer.TT_EOF)
      {
        if (tokenizer.ttype == StreamTokenizer.TT_WORD)
        {
          //if (wordCount.containsKey(tokenizer.sval)
          System.out.println(tokenizer.sval);
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
