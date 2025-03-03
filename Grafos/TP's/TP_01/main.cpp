#include <iostream>
#include <vector>
#include <algorithm>

// Grafo Nao-Direcionado e simples
// A B C D E F == 0 1 2 3 4 5

// Utilziado matriz para acessar rapido uma aresta
std::vector<std::vector<int>> adjacentMatrix =
{
//   A, B, C, D, E, F
    {0, 1, 0, 1, 1, 0}, // A
    {1, 0, 1, 1, 1, 0}, // B
    {0, 1, 0, 1, 1, 1}, // C
    {1, 1, 1, 0, 0, 1}, // D
    {1, 1, 1, 0, 0, 1}, // E
    {0, 0, 1, 1, 1, 0}  // F
};

// Considerando que a posicao i - 1 e i nunca serao iguais, verifica se existe uma aresta entre os vertices em sequencia
bool hasWalk(std::vector<int> vertex);

// Todas permutacoes possivel com groupSize elementos em um total existente de totalElements elementos
std::vector<std::vector<int>> makePermutations(int totalElements, int groupSize);
void makePermutationsRec(const int& totalElements, const int& groupSize, int actualSize, std::vector<int>& actualGroup, std::vector<std::vector<int>>& finalGroup, std::vector<bool>& usedVertex);

// Total de ciclos em um grafo utilizando todas as permutacoes de vertices
int totalCyclesWithPermutations();

// Chama a DFS para detectar ciclos em todos os vertices
int totalCyclesWithDFS();
// Para cada vertice, achar ciclos que iniciam e terminam nele, apenas com vertices "maiores" que o inicial para evitar repeticoes
int countCyclesFromVertexDFS(const int& startedVertex, int actualVertex, const int& totalVertex, int walkSize, std::vector<bool>& visitedVertex, int& secondVertex);

int main()
{
    std::cout << "Permutations: " << totalCyclesWithPermutations() << std::endl;
    std::cout << "DFS: " << totalCyclesWithDFS() << std::endl;

    return 0;
}

// -------------------------------------- DFS --------------------------------------

int totalCyclesWithDFS()
{
    int totalVertex = adjacentMatrix.size();
    int totalCycle = 0;

    for (int i = 0; i < totalVertex - 2; i++)
    {
        std::vector<bool> visitedVertex(totalVertex, false);
        std::vector<int> actualWalk;
        int secondVertex = -1;
        totalCycle += countCyclesFromVertexDFS(i, i, totalVertex, 1, visitedVertex, secondVertex);
    }

    return totalCycle;
}

int countCyclesFromVertexDFS(const int& startedVertex, int actualVertex, const int& totalVertex, int walkSize, std::vector<bool>& visitedVertex, int& secondVertex)
{
    visitedVertex[actualVertex] = true;
    
    int cycleCount = 0;
    if (walkSize >= 3 && adjacentMatrix[actualVertex][startedVertex] == 1 && secondVertex < actualVertex)
        cycleCount++;
    
    for (int i = startedVertex + 1; i < totalVertex; i++)
    {
        if (!visitedVertex[i] && adjacentMatrix[actualVertex][i] == 1)
        {
            if (actualVertex == startedVertex)
                secondVertex = i;

            cycleCount += countCyclesFromVertexDFS(startedVertex, i, totalVertex, walkSize + 1, visitedVertex, secondVertex);
        }
    }

    visitedVertex[actualVertex] = false;
    return cycleCount;
}

// -------------------------------------- Permutations --------------------------------------

int totalCyclesWithPermutations()
{
    int totalCycle = 0;
    int totalVertex = adjacentMatrix.size();
    for (int i = 3; i <= totalVertex; i++)
    {
        int sumCycle = 0;
        std::vector<std::vector<int>> permutationGroup = makePermutations(totalVertex, i);
        for (std::vector<int> permutation : permutationGroup)
        {
            // Criar o ciclo
            permutation.push_back(permutation[0]);
            if (hasWalk(permutation))
                sumCycle++;
        }

        totalCycle += sumCycle / (i * 2);
    }

    return totalCycle;
}

std::vector<std::vector<int>> makePermutations(int totalElements, int groupSize)
{
    std::vector<std::vector<int>> finalGroup;
    std::vector<int> actualGroup;
    std::vector<bool> usedVertex(totalElements, false);
    
    makePermutationsRec(totalElements, groupSize, 0, actualGroup, finalGroup, usedVertex);
    
    return finalGroup;
}

void makePermutationsRec(const int& totalElements, const int& groupSize, int actualSize, std::vector<int>& actualGroup, std::vector<std::vector<int>>& finalGroup, std::vector<bool>& usedVertex)
{
    if (actualSize == groupSize)
    {
        finalGroup.push_back(actualGroup);
        return;
    }
    
    for (int i = 0; i < totalElements; i++)
    {
        if (!usedVertex[i])
        {
            actualGroup.push_back(i);
            usedVertex[i] = true;
            makePermutationsRec(totalElements, groupSize, actualSize + 1, actualGroup, finalGroup, usedVertex);
            actualGroup.pop_back();
            usedVertex[i] = false;
        }
    }
}

bool hasWalk(std::vector<int> vertex)
{
    int size = vertex.size();
    if (size == 1)
        return false; // Grafo simples nao possui aresta de v -> v

    int i = 1;
    while (i < size)
    {
        if (adjacentMatrix[vertex[i - 1]][vertex[i]] != 1)
            return false;

        i++;
    }

    return true;
}