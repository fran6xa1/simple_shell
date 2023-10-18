#include "shell.h"

void write_stdout(const char *str, size_t len)
{
	ssize_t bytes_written = write(STDOUT_FILENO, str, len);
	if (bytes_written == -1)
	{
		perror("write");
		exit(EXIT_FAILURE);
	}
}

int main(__attribute__((unused))int ac, char **av)
{
	int status = 0;
	int line_num = 1;
	char *shell_name = NULL;
	int bytes_read, is_separated = FALSE, i;
	size_t buf_size = 1;
	char *buf = NULL, *buf_ptr, *buf_tmp, **args = NULL;

	shell_name = custom_strdup(*av);
	environ = my_copy_array(environ, my_list_length(environ, NULL));
	signal(SIGINT, SIG_IGN);
	buf = malloc(1);

	if (buf == NULL)
		exit(EXIT_FAILURE);

	while (1)
	{
		if (is_separated == FALSE)
		{
			if (isatty(STDIN_FILENO) == 1)
				write_stdout("my_shell$ ", 10);

			bytes_read = getline(&buf, &buf_size, stdin);

			if (bytes_read == -1)
				break;

			if (bytes_read == 1)
			{
				line_num++;
				continue;
			}

			buf[bytes_read - 1] = '\0';
			buf = sanitize_input(buf, &buf_size);

			if (buf_size == 0)
			{
				line_num++;
				continue;
			}

			buf_ptr = buf;
		}
		else
			buf_ptr = buf_tmp;

		buf_tmp = NULL;
		args = split_string(buf_ptr, ' ', &buf_tmp);
		is_separated = (buf_tmp != NULL);
		i = handle_commands(args);
		free(args);

		if (is_separated == FALSE)
			line_num++;

		if (i == EXIT_SHELL)
			break;
	}

	free(buf);
	my_alias_function(NULL, TRUE);
	my_free_array(environ);
	free(shell_name);
	return (status % 256);
}
