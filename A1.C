#include "test.h"
#include <string.h>

void generate_selections(int a[], int n, int k, int b[], void *data, void (*process_selection)(int *b, int k, void *data)) {
    for (int i = 0; i < k; ++i) {
        b[i] = a[i];
    }

    while (1) {
        process_selection(b, k, data);

        int j = k - 1;
        while (j >= 0 && b[j] == a[n - k + j]) {
            j--;
        }
        if (j < 0) {
            break;
        }

        b[j]++;
        for (int l = j + 1; l < k; ++l) {
            b[l] = b[l - 1] + 1;
        }
    }
}

void generate_splits(const char *source, const char *dictionary[], int nwords, char buf[], void *data, void (*process_split)(char buf[], void *data)) {
    int source_len = strlen(source);
    int buf_len = 0;
    int start = 0;

    for (int i = 0; i < nwords; ++i) {
        int word_len = strlen(dictionary[i]);
        if (source_len - start >= word_len && strncmp(source + start, dictionary[i], word_len) == 0) {
            if (buf_len > 0) {
                buf[buf_len++] = ' ';
            }
            strcpy(buf + buf_len, dictionary[i]);
            buf_len += word_len;
            start += word_len;
            if (start == source_len) {
                process_split(buf, data);
                break;
            }
        }
    }
}

void previous_permutation(int a[], int n) {
    int i = n - 1;
    while (i > 0 && a[i - 1] <= a[i]) {
        i--;
    }

    if (i > 0) {
        int j = n - 1;
        while (a[j] >= a[i - 1]) {
            j--;
        }

        int temp = a[i - 1];
        a[i - 1] = a[j];
        a[j] = temp;

        j = n - 1;
        while (i < j) {
            temp = a[i];
            a[i] = a[j];
            a[j] = temp;
            i++;
            j--;
        }
    }
}

typedef struct {
    int index;
    int err;
    int first;
} state_t;

static void test_selections_2165(int b[], int k, void *data) {
    state_t *s = (state_t *)data;
    if (s->first) {
        s->err = 0;
        s->first = 0;
    }
    switch (s->index) {
    case 0:
        if ((b[0] != 2) || (b[1] != 1)) {
            s->err = 1;
        }
        break;
    case 1:
        if ((b[0] != 2) || (b[1] != 6)) {
            s->err = 1;
        }
        break;
    case 2:
        if ((b[0] != 2) || (b[1] != 5)) {
            s->err = 1;
        }
        break;
    case 3:
        if ((b[0] != 1) || (b[1] != 6)) {
            s->err = 1;
        }
        break;
    case 4:
        if ((b[0] != 1) || (b[1] != 5)) {
            s->err = 1;
        }
        break;
    case 5:
        if ((b[0] != 6) || (b[1] != 5)) {
            s->err = 1;
        }
        break;
    default:
        s->err = 1;
    }
    ++(s->index);
}

void count_selections(int b[], int k, void *data) {
    int d = (int)data;
    ++*d;
}

typedef struct {
    int b[100];
} selection_t;

void last_selection(int b[], int k, void *data) {
    selection_t s = (selection_t)data;
    for (int i = 0; i < k; ++i) {
        s->b[i] = b[i];
    }
}

int main() {
    run_tests((test_t[]) {
        TEST(generate_selections),
        TEST(generate_splits),
        TEST(previous_permutation),
        0
    });
    return 0;
}