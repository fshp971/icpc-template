import java.io.*;
import java.util.*;
import java.math.*;

public class Main {
	//public static void main(String[] args) throws FileNotFoundException {
	public static void main(String[] args) {
		//普通读入
		Scanner in = new Scanner( new BufferedInputStream(System.in) );
        in.close(); // 终止语句

		//判断文件末尾
		while(in.hasNextInt());

		//文件读入
		Scanner in = new Scanner(new File("in.txt"));
		PrintWriter out = new PrintWriter("out.txt");
		//读入结束后执行如下代码
		out.flush();
		out.close();

		//stdin快速度入，需结合InputReader食用
		InputStream inputStream = System.in;
		InputReader in = new InputReader(inputStream);

		//快速输出到stdout
		OutputStream outputStream = System.out;
		PrintWriter out = new PrintWriter(outputStream);
		out.close();
	}

	//stdin快速度入
	static class InputReader {
		public BufferedReader reader;
		public StringTokenizer tokenizer;

		public InputReader(InputStream stream) {
			reader = new BufferedReader(new InputStreamReader(stream), 32768);
			tokenizer = null;
		}

		public String next() {
			while (tokenizer == null || !tokenizer.hasMoreTokens()) {
				try {
					tokenizer = new StringTokenizer(reader.readLine());
				} catch (IOException e) {
					throw new RuntimeException(e);
				}
			}
			return tokenizer.nextToken();
		}

		public int nextInt() {
			return Integer.parseInt(next());
		}
	}
}
