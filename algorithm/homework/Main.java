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
    static final long inf = 100000000;
    public static void main(String args[]) {
        Scanner sc = new Scanner(System.in);
        StringTokenizer stk;
        int N = sc.nextInt();
        int E = sc.nextInt();
        ArrayList<Edge> a = new ArrayList<Edge>();
        for (int i=0; i<E; i++) {
            int from = sc.nextInt();
            int to = sc.nextInt();
            int cost = sc.nextInt();
            a.add(new Edge(from, to, cost));
        }
        long[] dist = new long[N+1];
        for (int i=1; i<=N; i++) {
            dist[i] = inf;
        }
        dist[1] = 0;
        boolean negative_cycle = false;
        for (int i=1; i<=N; i++) {
            for (Edge edge : a) {
                int x = edge.from;
                int y = edge.to;
                int z = edge.cost;
                if (dist[x] != inf && dist[y] > dist[x]+z) {
                    dist[y] = dist[x]+z;
                    if (i == N) {
                        negative_cycle = true;
                    }
                }
            }
        }
        if (negative_cycle) {
            System.out.println("-1");
        } else {
            for (int i=1; i<=N; i++) {
                if (dist[i] == inf) dist[i] = -1;
                System.out.print(dist[i]);
                if (i != N)
                    System.out.print(" ");
                else
                    System.out.print("\n");
            }
        }
    }
}
