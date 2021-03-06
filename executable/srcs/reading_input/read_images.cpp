#include "executable.hpp"

void        recording_tags(t_info *info, int index, char *str) {

    char    *tmp;
    int     i;
    int     j;

    info->input[index]->tags = (long long *)malloc(sizeof(long long) * info->input[index]->number_of_tags);
    i = 0;
    while (i < info->input[index]->number_of_tags)
    {
        if (*str == '\0')
            error("The listed number for tags doesn't match the actual");
        j = 0;
        while (str[j] != ' ' && str[j] != '\0')
            ++j;
        tmp = (char *)malloc(sizeof(char) * (j + 1));
        j = 0;
        while (*str != ' ' && *str != '\0')
        {
            tmp[j] = *str;
            ++str;
            ++j;
        }
        tmp[j] = '\0';
        info->input[index]->tags[i++] = from_string_to_num(tmp);
        if (*str != '\0')
            ++str;
    }
    if (*str != '\0')
        error("The listed number for tags doesn't match the actual");
}

int         read_images(t_info *info, std::string line, int index) {

    char    *str = new char[line.length() + 1];

    strcpy(str, line.c_str());
    if (*str == 'H')
        info->input[index]->position = 0;
    else if (*str == 'V')
        info->input[index]->position = 1;
    else
        return (-1);
    ++str;
    if (*str != ' ')
        return (-1);
    ++str;
    info->input[index]->number_of_tags = atoi(&str[0]);
    if (info->input[index]->number_of_tags < 0 || info->input[index]->number_of_tags > 100000)
        error("The listed number for tags is invalid");
    while (*str >= '0' && *str <= '9')
        ++str;
    if (*str != ' ')
        return (-1);
    ++str;
    recording_tags(info, index, str);
    return (1);
}