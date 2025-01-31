#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#define MAX 100
#define INF 1000000

typedef struct {
    int x, y;
} Point;

typedef struct {
    int distance;
    Point point;
} QueueNode;

typedef struct {
    QueueNode data[MAX * MAX];
    int size;
} PriorityQueue;

void initPriorityQueue(PriorityQueue *pq) {
    pq->size = 0;
}

void enqueue(PriorityQueue *pq, QueueNode node) {
    pq->data[pq->size++] = node;
    int i = pq->size - 1;

    // Up-heap bubbling
    while (i > 0 && pq->data[i].distance < pq->data[(i - 1) / 2].distance) {
        QueueNode temp = pq->data[i];
        pq->data[i] = pq->data[(i - 1) / 2];
        pq->data[(i - 1) / 2] = temp;
        i = (i - 1) / 2;
    }
}

QueueNode dequeue(PriorityQueue *pq) {
    QueueNode minNode = pq->data[0];
    pq->data[0] = pq->data[--pq->size];

    int i = 0;
    while (i * 2 + 1 < pq->size) {
        int smallest = i;
        int left = i * 2 + 1;
        int right = i * 2 + 2;

        if (left < pq->size && pq->data[left].distance < pq->data[smallest].distance) {
            smallest = left;
        }
        if (right < pq->size && pq->data[right].distance < pq->data[smallest].distance) {
            smallest = right;
        }
        if (smallest != i) {
            QueueNode temp = pq->data[i];
            pq->data[i] = pq->data[smallest];
            pq->data[smallest] = temp;
            i = smallest;
        } else {
            break;
        }
    }

    return minNode;
}

int isQueueEmpty(PriorityQueue *pq) {
    return pq->size == 0;
}
// BFS Function to Find All Routes
void solveMazeBFSAllRoutes(int rows, int cols, int maze[rows][cols], Point start, Point end) {
    typedef struct {
        Point path[MAX];
        int length;
    } Path;

    typedef struct {
        Path queue[MAX * MAX];
        int front, rear;
    } Queue;

    void initQueue(Queue *q) {
        q->front = q->rear = -1;
    }

    int isQueueEmpty(Queue *q) {
        return q->front == -1 || q->front > q->rear;
    }

    void enqueue(Queue *q, Path p) {
        if (q->rear < MAX * MAX - 1) {
            if (q->front == -1) q->front = 0;
            q->queue[++q->rear] = p;
        }
    }

    Path dequeue(Queue *q) {
        return q->queue[q->front++];
    }

    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    int routeCount = 0;

    // Initialize queue
    Queue q;
    initQueue(&q);

    Path initialPath;
    initialPath.length = 1;
    initialPath.path[0] = start;
    enqueue(&q, initialPath);

    printf("\n  All Possible Routes (BFS):\n");

    while (!isQueueEmpty(&q)) {
        Path currentPath = dequeue(&q);
        Point current = currentPath.path[currentPath.length - 1];

        // Check if endpoint is reached
        if (current.x == end.x && current.y == end.y) {
            routeCount++;
            printf("  Route %d: ", routeCount);
            for (int i = 0; i < currentPath.length; i++) {
                printf("(%d, %d)", currentPath.path[i].x, currentPath.path[i].y);
                if (i < currentPath.length - 1) printf(" -> ");
            }
            printf("\n");
            continue;
        }

        // Explore neighbors
        for (int i = 0; i < 4; i++) {
            int nx = current.x + directions[i][0];
            int ny = current.y + directions[i][1];

            if (nx >= 0 && nx < rows && ny >= 0 && ny < cols && maze[nx][ny] == 0) {
                int alreadyInPath = 0;

                // Check if this point is already in the current path
                for (int j = 0; j < currentPath.length; j++) {
                    if (currentPath.path[j].x == nx && currentPath.path[j].y == ny) {
                        alreadyInPath = 1;
                        break;
                    }
                }

                if (!alreadyInPath) {
                    Path newPath = currentPath;
                    newPath.path[newPath.length++] = (Point){nx, ny};
                    enqueue(&q, newPath);
                }
            }
        }
    }

    if (routeCount == 0) {
        printf("  No routes found using BFS.\n");
    }
}

// DFS Function to Find All Routes
void solveMazeDFSAllRoutesHelper(int rows, int cols, int maze[rows][cols], Point path[MAX], int pathLength, Point current, Point end, int *routeCount) {
    if (current.x == end.x && current.y == end.y) {
        (*routeCount)++;
        printf("  Route %d: ", *routeCount);
        for (int i = 0; i < pathLength; i++) {
            printf("(%d, %d)", path[i].x, path[i].y);
            if (i < pathLength - 1) printf(" -> ");
        }
        printf("\n");
        return;
    }

    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    for (int i = 0; i < 4; i++) {
        int nx = current.x + directions[i][0];
        int ny = current.y + directions[i][1];

        if (nx >= 0 && nx < rows && ny >= 0 && ny < cols && maze[nx][ny] == 0) {
            int alreadyInPath = 0;

            // Check if this point is already in the current path
            for (int j = 0; j < pathLength; j++) {
                if (path[j].x == nx && path[j].y == ny) {
                    alreadyInPath = 1;
                    break;
                }
            }

            if (!alreadyInPath) {
                path[pathLength] = (Point){nx, ny};
                solveMazeDFSAllRoutesHelper(rows, cols, maze, path, pathLength + 1, (Point){nx, ny}, end, routeCount);
            }
        }
    }
}

void solveMazeDFSAllRoutes(int rows, int cols, int maze[rows][cols], Point start, Point end) {
    Point path[MAX];
    path[0] = start;

    int routeCount = 0;

    printf("\n  All Possible Routes (DFS):\n");
    solveMazeDFSAllRoutesHelper(rows, cols, maze, path, 1, start, end, &routeCount);

    if (routeCount == 0) {
        printf("  No routes found using DFS.\n");
    }
}

void solveMazeDijkstra(int rows, int cols, int maze[rows][cols], Point start, Point end) {
    int distance[rows][cols];
    Point previous[rows][cols];
    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    PriorityQueue pq;
    initPriorityQueue(&pq);

    // Initialize distances to INF and previous to invalid points
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            distance[i][j] = INF;
            previous[i][j] = (Point){-1, -1};
        }
    }

    // Start point distance is 0
    distance[start.x][start.y] = 0;
    enqueue(&pq, (QueueNode){0, start});

    while (!isQueueEmpty(&pq)) {
        QueueNode currentNode = dequeue(&pq);
        Point current = currentNode.point;

        // Stop if we reach the end point
        if (current.x == end.x && current.y == end.y) break;

        // Explore neighbors
        for (int i = 0; i < 4; i++) {
            int nx = current.x + directions[i][0];
            int ny = current.y + directions[i][1];

            if (nx >= 0 && nx < rows && ny >= 0 && ny < cols && maze[nx][ny] == 0) {
                int newDistance = distance[current.x][current.y] + 1;

                if (newDistance < distance[nx][ny]) {
                    distance[nx][ny] = newDistance;
                    previous[nx][ny] = current;
                    enqueue(&pq, (QueueNode){newDistance, (Point){nx, ny}});
                }
            }
        }
    }

    // Trace back the shortest path
    if (distance[end.x][end.y] == INF) {
        printf("\n  No path found using Dijkstra's algorithm.\n");
    } else {
        printf("\n  Shortest Path (Dijkstra):\n  ");
        Point path[MAX];
        int pathLength = 0;
        Point current = end;

        while (current.x != -1 && current.y != -1) {
            path[pathLength++] = current;
            current = previous[current.x][current.y];
        }

        // Print the path
        for (int i = pathLength - 1; i >= 0; i--) {
            printf("(%d, %d)", path[i].x, path[i].y);
            if (i > 0) printf(" -> ");
        }
        printf("\n  Path Length: %d\n", distance[end.x][end.y]);

        // Display maze with the shortest path
        char solutionMaze[rows][cols];
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                solutionMaze[i][j] = maze[i][j] == 1 ? '1' : '0';
            }
        }

        for (int i = 0; i < pathLength; i++) {
            solutionMaze[path[i].x][path[i].y] = '*';
        }
        
        printf("\n  Maze with Shortest Path:\n  ");
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
            
            if (solutionMaze[i][j] == '*') {
                printf("🟩 ");  
            }
            else if (solutionMaze[i][j] == '0') {
                printf("⬜ ");  // Path
            } else if (solutionMaze[i][j] == '1') {
                printf("❌ ");  // Wall
            }
        }
        printf("\n  ");
        }
    }
}


// Function to generate a random maze with at least one guaranteed path
void generateMazeWithPath(int rows, int cols, int maze[rows][cols]) {
    srand(time(0)); // Seed for random number generator
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            maze[i][j] = 1;
        }
    }

    // Create a guaranteed path from (0, 0) to (rows-1, cols-1)
    int x = 0, y = 0;
    maze[x][y] = 0; // Start point
    while (x < rows - 1 || y < cols - 1) {
        if (x == rows - 1) {
            y++; // Move right
        } else if (y == cols - 1) {
            x++; // Move down
        } else if (rand() % 2) {
            x++; // Randomly choose to move down
        } else {
            y++; // Randomly choose to move right
        }
        maze[x][y] = 0; // Mark the path
    }

    // Randomly set additional paths (optional, for variety)
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (maze[i][j] == 1 && rand() % 4 == 0) { // Add random paths (probability 25%)
                maze[i][j] = 0;
            }
        }
    }
}

// Function to print the maze
void printMaze(int rows, int cols, int maze[rows][cols]) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (maze[i][j] == 0) {
                printf("⬜ ");  // Path
            } else if (maze[i][j] == 1) {
                printf("❌ ");  // Wall
            }
               
            
        }
        printf("\n  ");
    }
}


// Main Function
int main() {
    int rows, cols,choice1,choice2,gen, mazesel,flag;
    do{
         printf("\n\t*ੈ✩‧₊˚ \033[1;33mᗰ ᗩ ᘔ E  ᔕ O ᒪ ᐯ E ᖇ \033[0m*ੈ✩‧₊˚ \n\n");
        printf("  Enter the number of rows and columns in the maze : ");
        scanf("%d %d", &rows, &cols);

        int maze[rows][cols];
        printf("\n  MAZE Solver - MENU\n\t1.Enter MAZE manually\n\t2.Generate a MAZE\n  Enter your choice : ");
        scanf("%d",&mazesel);
        switch(mazesel){
            case 1:
                printf("  Enter the maze (0 for path, 1 for wall) :\n");
                for (int i = 0; i < rows; i++) {
                    for (int j = 0; j < cols; j++) {
                        scanf("%d", &maze[i][j]);
                    }
                }
                break;
            case 2:
                do{
                    generateMazeWithPath(rows, cols, maze);
                    printf("\n  Generated Maze with Guaranteed Path:\n  ");
                    printMaze(rows, cols, maze);
                    printf("\n  Continue(1) or Regenerate(0) : ");
                    scanf("%d",&gen);
                }while(gen==0);
                break;
        }
        system("clear");
         printf("\n\t*ੈ✩‧₊˚ \033[1;33mᗰ ᗩ ᘔ E  ᔕ O ᒪ ᐯ E ᖇ \033[0m*ੈ✩‧₊˚ \n\n");
        printf("  Entered MAZE(%dx%d) : \n\n  ",rows,cols);
        printMaze(rows, cols, maze);
        Point start, end;
        do{
            flag=0;
            printf("\n  Enter the start point (row and column) : ");
            scanf("%d %d", &start.x, &start.y);
            printf("\n  Enter the end point (row and column) : ");
            scanf("%d %d", &end.x, &end.y);
            if(start.x>=rows || start.y >= cols || end.x>=rows || end.y >= cols ){
                printf("  Please enter valid start and end points...!\n");
                flag=1;
            }
        }while(flag==1);
        system("clear");
         printf("\n\t*ੈ✩‧₊˚ \033[1;33mᗰ ᗩ ᘔ E  ᔕ O ᒪ ᐯ E ᖇ \033[0m*ੈ✩‧₊˚ \n\n");
        printf("  Entered MAZE(%dx%d) : \n\n  ",rows,cols);
        printMaze(rows, cols, maze);
        printf("\n  Start : (%d,%d)\t|    End : (%d,%d)",start.x,start.y,end.x,end.y);
        do{
            printf("\n\n  MAZE Solver - MENU\n\t1.Solve using BFS\n\t2.Solve using DFS\n\t3.Shortest path using Dijikstra's algorithm\n\t4.All above\n\t5.Exit\n  Enter your choice : ");
            scanf("%d",&choice1);
            system("clear");
             printf("\n\t*ੈ✩‧₊˚ \033[1;33mᗰ ᗩ ᘔ E  ᔕ O ᒪ ᐯ E ᖇ \033[0m*ੈ✩‧₊˚ \n\n");
            printf("  Entered MAZE(%dx%d) : \n\n  ",rows,cols);
            printMaze(rows, cols, maze);
            printf("\n  Start : (%d,%d)\t|    End : (%d,%d)",start.x,start.y,end.x,end.y);
        
            switch(choice1){
                case 1:
                    printf("\n  Solving with BFS...\n");
                    solveMazeBFSAllRoutes(rows, cols, maze, start, end);
                    break;
                case 2:
                    printf("\n  Solving with DFS...\n");
                    solveMazeDFSAllRoutes(rows, cols, maze, start, end);
                    break;
                case 3:
                    solveMazeDijkstra(rows, cols, maze, start, end);
                    break;
                case 4:
                    printf("\n  Solving with BFS...\n");
                    solveMazeBFSAllRoutes(rows, cols, maze, start, end);
                    printf("\n  Solving with DFS...\n");
                    solveMazeDFSAllRoutes(rows, cols, maze, start, end);
                    solveMazeDijkstra(rows, cols, maze, start, end);
                    break;
                case 5:
                    printf("  Exiting...\n");
                    break;
                default:
                    printf("  Invalid Input\n");
    
            }
        }while(choice1!=5);
        system("clear");
         printf("\n\t*ੈ✩‧₊˚ \033[1;33mᗰ ᗩ ᘔ E  ᔕ O ᒪ ᐯ E ᖇ \033[0m*ੈ✩‧₊˚ \n\n");
        printf("  Do you want to restart(1) or exit(0) 🥺 : ");
        scanf("%d",&choice2);
        if(choice2==1)
            system("clear");
    }while(choice2!=0);
    return 0;
}