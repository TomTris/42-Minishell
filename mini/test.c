/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 15:22:13 by qdo               #+#    #+#             */
/*   Updated: 2024/05/22 09:42:49 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>

int main() {
    char	path[1024];

	// getcwd(path, 1024);

    if (access("/", F_OK) == 0) {
        struct stat path_stat;
        if (stat("/", &path_stat) == 0) {
            if (S_ISREG(path_stat.st_mode)) {
                printf("%s is a regular file.\n", path);
            } else if (S_ISDIR(path_stat.st_mode)) {
                printf("%s is a directory.\n", path);
            } else {
                printf("%s is neither a regular file nor a directory.\n", path);
            }
        } else {
            perror("stat error");
            return 1;
        }
    } else {
        perror("access error");
        return 1;
    }

    return 0;
}
