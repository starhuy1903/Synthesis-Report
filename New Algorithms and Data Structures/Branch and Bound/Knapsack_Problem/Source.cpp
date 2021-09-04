#include <iostream>
using namespace std;

struct Node
{
	int x, values, weights, UB;
};

//sort all the iteam in descending in value/weight
//define a function to calculate the upperbound of a node
//Queue operations

void enqueue(Node* queue, int N, Node p)
{
	if (p.UB < queue[N - 1].UB || N - 1 == -1) {
		queue[N] = p;
		return;
	}

	queue[N - 1] = queue[N - 2];
	enqueue(queue, N - 1, p);
}
Node dequeue(Node* queue, int N)
{
	if (N == 1)
		return queue[0];

	Node p = dequeue(queue, N - 1);
	queue[N - 2] = queue[N - 1];
	queue[N - 1].UB = -1;
	return p;
}
bool isEmpty(Node* queue)
{
	return queue[0].UB == -1 ? true : false;
}
Node* initQueue(int N)
{
	Node* queue = new Node[N];
	for (int i = 0; i < N; i++)
		queue[i].UB = -1;

	return queue;
}


void sortValuebyWeight(int* V, int* W, int N)
{
	int v, w, j;
	for (int i = 1; i < N; i++)
	{
		v = V[i];
		w = W[i];
		j = i - 1;
		while (j >= 0 && (double)V[j] / W[j] < (double)v / w)
		{
			V[j + 1] = V[j];
			W[j + 1] = W[j];
			j--;
		}

		V[j + 1] = v;
		W[j + 1] = w;
	}
}
int upperbound(Node& p, int* V, int* W, int N, int M)
{
	int UB = p.values;
	int w = p.weights;

	int i = p.x + 1;
	while (i < N && w + W[i] < M) {
		UB += V[i];
		w += W[i];
		i++;
	}

	if (i < N)
		UB += (M - w) * V[i] / W[i];

	p.UB = UB;
	return UB;
}
int solveKapsack(int* V, int* W, int N, int M)
{
	sortValuebyWeight(V, W, N);
	Node* queue = initQueue(N);

	Node p_pre{ -1, 0, 0 };
	p_pre.UB = upperbound(p_pre, V, W, N, M);
	enqueue(queue, N, p_pre);

	int maxValue = 0;
	Node p{ 0 };
	while (!isEmpty(queue))
	{
		p_pre = dequeue(queue, N);
		if (p_pre.x == N - 1||p_pre.UB < maxValue)
			continue;

		p.x = p_pre.x + 1;

		//x is included in the sack
		p.values = p_pre.values + V[p.x];
		p.weights = p_pre.weights + W[p.x];
		p.UB = upperbound(p, V, W, N, M);
		//if the node larger than the current values,
		//put it into the queue for further searches
		if (p.UB >= maxValue && p.weights <= M)
			enqueue(queue, N, p);

		if (p.values >= maxValue && p.weights <= M)
			maxValue = p.values;

		//x is not included in the sack
		p.values = p_pre.values;
		p.weights = p_pre.weights;
		p.UB = upperbound(p, V, W, N, M);

		if (p.UB >= maxValue && p.weights <= M)
			enqueue(queue, N, p);
	}

	delete[]queue;
	return maxValue;
}

int main()
{
	int N = 4, M = 16;
	int V[] = { 10, 10, 12, 18 }, W[] = { 2, 4, 6, 9 };

	cout << solveKapsack(V, W, N, M);

	return 0;
}