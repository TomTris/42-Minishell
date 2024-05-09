/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ca.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 22:06:32 by qdo               #+#    #+#             */
/*   Updated: 2024/05/08 22:24:29 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdio.h>
#include <stdlib.h>

int main() {
    // Define the name of the environment variable you want to retrieve
    char* var_name = "PATH";

    // Use getenv to retrieve the value of the environment variable
    char* var_value = getenv(var_name);

    // Check if the environment variable exists
    if (var_value != NULL) {
        printf("%s = %s\n", var_name, var_value);
    } else {
        printf("Environment variable '%s' not found.\n", var_name);
    }

    return 0;
}
