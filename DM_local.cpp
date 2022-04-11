#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <queue>

using namespace std;

const string  IN_PATH = "in.txt",
             OUT_PATH = "out.txt",
             INF_PATH = "info.txt";

const char  REL = 1,  // relation - связь
           CREL = 2;  // checked relation - проверенная связь

int BFS(vector<vector<int>> &graph);

int main()
{
   setlocale(0, "");

   // E - кол-во ребер, V - кол-во вершин
   int E, V;
   vector<vector<int>> graph;

   ifstream stream(INF_PATH);
   if (!stream.is_open())
   {
      cerr << "Не удалось открыть файл " << INF_PATH;
      return -1;
   }
   stream >> E >> V;
   stream.close();

   stream = ifstream(IN_PATH);
   if (!stream.is_open())
   {
      cerr << "Не удалось открыть файл " << IN_PATH;
      return -1;
   }

   graph.resize(V);
   for (int i = 0; i < V; i++)
      graph[i].resize(V);

   for (int r, c, i = 0; i < E; i++)
   {
      stream >> r >> c;

      graph[r][c] = REL;
      graph[c][r] = REL;
   }

   ofstream out = ofstream(OUT_PATH);

   if (E - BFS(graph) == 0)
   {
       if (E == V - 1)
           out << "Дерево." << endl;
       else out << "Не дерево: есть цикл." << endl;
   }
   else out << "Не дерево: компонент связности больше 1." << endl;

   cout << "Ok!";

   return 0;
}

int BFS(vector<vector<int>> &graph)
{
   int CE = 0; // СE (checked edges) - кол-во вершин, которые алгоритм перебрал

   queue<int> queue;
   queue.push(0);

   while (!queue.empty())
   {
      int r = queue.front();
      queue.pop();

      for (int c = 0; c < graph.size(); c++)
      {
         if (graph[r][c] == REL)
         {
            queue.push(c);
            graph[r][c] = CREL;
            graph[c][r] = CREL;

            CE++;
         }
      }
   }

   return CE;
}