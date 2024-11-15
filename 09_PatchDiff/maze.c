#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

int main(int argc, char *argv[]) {
    int maze_size = 6;

    char pass = '.', wall = '#';

    int seed = time(NULL);
    srand(seed);

    char **maze = calloc(sizeof(char *), maze_size * 2 + 1);
    for (int i = 0; i < maze_size * 2 + 1; i++)
        maze[i] = calloc(sizeof(char), maze_size * 2 + 1);

    for (int i = 0; i < maze_size * 2 + 1; i++)
        for (int j = 0; j < maze_size * 2 + 1; j++)
            maze[i][j] = (i % 2 == 1 && j % 2 == 1) ? pass : wall;


    int num_of_cells_to_visit = maze_size * maze_size, num_of_visited_cells = 0;
    bool **visited_cells = calloc(sizeof(bool *), maze_size);
    for (int i = 0; i < maze_size; i++)
        visited_cells[i] = calloc(sizeof(bool), maze_size);

    for (int i = 0; i < maze_size; i++)
        for (int j = 0; j < maze_size; j++)
            visited_cells[i][j] = false;

    int curr_i = 0, curr_j = 0;
    int *i_history = calloc(sizeof(int), maze_size * maze_size);
    int *j_history = calloc(sizeof(int), maze_size * maze_size);
    for (int i = 0; i < maze_size * maze_size; i++) {
        i_history[i] = -1;
        j_history[i] = -1;
    }
    int history_pos;
    int *unvisited_neighbours_i = calloc(sizeof(int), 4);
    int *unvisited_neighbours_j = calloc(sizeof(int), 4);
    history_pos = 0;
    visited_cells[curr_i][curr_j] = true;
    i_history[history_pos] = curr_i;
    j_history[history_pos] = curr_j;
    num_of_visited_cells++;
    do {
        for (int i = 0; i < 4; i++) {
            unvisited_neighbours_i[i] = -1;
            unvisited_neighbours_j[i] = -1;
        }
        int k = 0;
        if (curr_i > 0 && visited_cells[curr_i - 1][curr_j] == false) {
            unvisited_neighbours_i[k] = curr_i - 1;
            unvisited_neighbours_j[k] = curr_j;
            k++;
        }
        if (curr_i < (maze_size - 1) && visited_cells[curr_i + 1][curr_j] == false) {
            unvisited_neighbours_i[k] = curr_i + 1;
            unvisited_neighbours_j[k] = curr_j;
            k++;
        }
        if (curr_j > 0 && visited_cells[curr_i][curr_j - 1] == false) {
            unvisited_neighbours_i[k] = curr_i;
            unvisited_neighbours_j[k] = curr_j - 1;
            k++;
        }
        if (curr_j < (maze_size - 1) && visited_cells[curr_i][curr_j + 1] == false) {
            unvisited_neighbours_i[k] = curr_i;
            unvisited_neighbours_j[k] = curr_j + 1;
            k++;
        }

        if (k == 0) {
            if (history_pos == 0) {
                printf("Something gone wrong!\n");
                return -1;
            }
            history_pos--;
            curr_i = i_history[history_pos];
            curr_j = j_history[history_pos];
        } else {
            int r = rand() % k;
            maze[curr_i * 2 + 1 + (unvisited_neighbours_i[r] - curr_i)][curr_j * 2 + 1 + (unvisited_neighbours_j[r] - curr_j)] = pass;
            curr_i = unvisited_neighbours_i[r];
            curr_j = unvisited_neighbours_j[r];
            history_pos++;
            visited_cells[curr_i][curr_j] = true;
            num_of_visited_cells++;
            i_history[history_pos] = curr_i;
            j_history[history_pos] = curr_j;
        }
    } while (num_of_visited_cells < num_of_cells_to_visit);


    for (int i = 0; i < maze_size; i++) {
        free(visited_cells[i]);
    }
    free(visited_cells);
    free(i_history);
    free(j_history);
    free(unvisited_neighbours_i);
    free(unvisited_neighbours_j);

    for (int i = 0; i < maze_size * 2 + 1; i++) {
        printf("%s\n", maze[i]);
        free(maze[i]);
    }
    free(maze);

    return 0;
}
