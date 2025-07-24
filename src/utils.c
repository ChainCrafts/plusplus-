#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Define our own strdup if it's not available (e.g., on some Windows compilers) */
#if defined(_WIN32) && !defined(__GNUC__) && !defined(_POSIX_C_SOURCE)
char *strdup(const char *s)
{
    size_t len = strlen(s) + 1;
    char *new_str = malloc(len);
    if (new_str == NULL)
        return NULL;
    return (char *)memcpy(new_str, s, len);
}
#endif

/**
 * Create a file path by adding extension to base name
 * @param base Base filename
 * @param extension Extension to add (including the dot)
 * @param buffer Buffer to store the result
 * @param size Size of the buffer
 */
void create_filename(const char *base, const char *extension, char *buffer, size_t size)
{
    /* Handle both Windows and Unix paths */
    snprintf(buffer, size, "%s%s", base, extension);
}

/**
 * Safe strdup implementation
 * @param str String to duplicate
 * @return Newly allocated string or NULL if allocation fails
 */
char *safe_strdup(const char *str)
{
    if (str == NULL)
    {
        return NULL;
    }

    char *dup = strdup(str);
    if (dup == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    return dup;
}
