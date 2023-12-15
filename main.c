#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct client {
    double balance;
    char first_name[20];
    char surname[20];
    char id[10];
};

void set_data(char *arr, unsigned int length) {
    fgets(arr, length, stdin);
    arr[strcspn(arr, "\n")] = '\0'; // Remove newline character
}

void set_client(struct client *new_client, const double deposit) {
    if (deposit < 50) {
        printf("Insufficient funds!!!\n");
        return;
    }
    new_client->balance = deposit;
    printf("Enter client's first name: ");
    set_data(new_client->first_name, sizeof(new_client->first_name));
    printf("\nEnter client's surname: ");
    set_data(new_client->surname, sizeof(new_client->surname));
    printf("\nEnter client's id: ");
    set_data(new_client->id, sizeof(new_client->id));
    printf("\n");
}

void transaction(struct client *sender, struct client *receiver, double amount) {
    if (amount < 0) {
        printf("Invalid amount!!!\n");
        return;
    }
    sender->balance -= amount;
    receiver->balance += amount;
}

struct client_arr {
    size_t capacity;
    size_t size;
    struct client *current_clients;
};

void set_arr(struct client_arr *arr) {
    arr->capacity = 4;
    arr->size = 0;
    arr->current_clients = (struct client *)malloc(arr->capacity * sizeof(struct client));
}

void push_back(struct client_arr *arr, struct client *client_to_add) {
    if (arr->size == arr->capacity) {
        arr->capacity += arr->capacity / 2;
        struct client *new_arr = (struct client *)malloc(arr->capacity * sizeof(struct client));
        for (unsigned int i = 0; i < arr->size; ++i) {
            new_arr[i] = arr->current_clients[i];
        }
        free(arr->current_clients);
        arr->current_clients = new_arr;
    }
    arr->current_clients[arr->size] = *client_to_add;
    ++arr->size;
}

struct client *get_client(const unsigned int index, struct client_arr *arr) {
    if (index >= arr->size || index < 0) {
        printf("Index is out of bounds!!!\n");
        return NULL;
    } else {
        return &(arr->current_clients[index]);
    }
}

void print_client(const struct client *client) {
    printf("First name: %s |", client->first_name);
    printf("Surname: %s |", client->surname);
    printf("ID: %s |", client->id);
    printf("Balance: %.2lf\n", client->balance);
}

void delete_clients(struct client_arr *arr) {
    free(arr->current_clients);
    arr->size = 0;
    arr->capacity = 0;
}

void deposit_sum(struct client* client, const double sum){
    if(sum < 0 && sum < -(client->balance)){
        printf("Invalid sum!!! \n");
        return;
    }
    client->balance +=sum;
}

int main() {
    struct client_arr test_arr;
    set_arr(&test_arr);
    struct client test1;
    set_client(&test1, 2000);
    push_back(&test_arr, &test1);
    print_client(get_client(0, &test_arr));
    print_client(&test1);
    deposit_sum(&test1, 500);
    print_client(&test1);
    deposit_sum(&test1, -4000);
    print_client(&test1);
    delete_clients(&test_arr);

    return 0;
}
