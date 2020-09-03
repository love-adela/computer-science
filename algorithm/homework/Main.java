import java.util.*;
import java.io.FileReader;
import java.io.BufferedReader;
import java.io.PrintWriter;

class Edge {
    int from, to, cost;
    Edge(int from, int to, int cost) {
        this.from = from;
        this.to = to;
        this.cost = cost;
    }

}
public class Main {
    static final int MAX_N = 1000;
    static final int MAX_E = 100000;
    static final long inf = 100000000;
    static int[] Answer1 = new int[MAX_N+1];
    // static int[] Answer2 = new int[MAX_N+1];
    // static double time1, time2;

    public static void main(String args[]) {
        Scanner sc = new Scanner(System.in);
        StringTokenizer stk;
        ArrayList<Edge> a = new ArrayList<Edge>();

        for (int test_case =1; test_case <= 10; test_case++){
            int N = sc.nextInt();
            int E = sc.nextInt();
            for (int i=0; i<E; i++) {
                int from = sc.nextInt();
                int to = sc.nextInt();
                int cost = sc.nextInt();
                a.add(new Edge(from, to, cost));
            }
            // Debug
            // for (Edge edge : a) {
            //     System.out.printf("from:%d   to:%d    cost:%d\n", edge.from, edge.to, edge.cost);
            // }

            // long[] dist = new long[N+1];
            for (int i=1; i<=N; i++) {
                // dist[i] = inf;
                Answer1[i] = 1000000000; 
            }
            // dist[1] = 0;
            Answer1[1] = 0;
            boolean negative_cycle = false;
            for (int i=1; i<=N; i++) {
                for (Edge edge : a) {
                    int x = edge.from;
                    int y = edge.to;
                    int z = edge.cost;
                    if (Answer1[x] != 1000000000 && Answer1[y] > Answer1[x]+z) {
                        Answer1[y] = Answer1[x]+z;
                        if (i == N) {
                            negative_cycle = true;
                        }
                    }
                }
            }
            // if (negative_cycle) {
            //     System.out.println("-1");
            // } else {
            // System.out.println("#" + test_case);
            for (int i=1; i<=N; i++) {
                // if (dist[i] == inf) dist[i] = -1;
                System.out.print(Answer1[i]);
                if (i != N)
                    System.out.print(" ");
                else
                    System.out.print("\n");
            }
        }
    }
}