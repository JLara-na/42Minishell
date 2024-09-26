/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdin_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 13:33:34 by jlara-na          #+#    #+#             */
/*   Updated: 2024/09/26 19:07:57 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	unlink_heredocs(void	*token_ptr, void	*shell_ptr)
{
	t_token	*token;
	int		i;

	(void)shell_ptr;
	token = (t_token *)token_ptr;
	i = -1;
	if (token->heredoc)
	{
		while (token->heredoc[++i])
		{
			unlink(token->heredoc[i]);
		}
	}
}

char	*new_temp_file(void)
{
	static int	file_num;
	char		*file_num_str;
	char		*filename;

	file_num_str = ft_itoa(file_num++);
	filename = ft_strjoin(".tmp_filename_heredoc_", file_num_str);
	free(file_num_str);
	return (filename);
}

char	*do_heredoc(char *str, t_token	*token)
{
	char	*line;
	char	*filename;
	int		fd;

	(void)token;
	filename = new_temp_file();
	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (fd == -1)
	{
		printf("OPEN ERROR\n");
		return (NULL);
	}
	line = readline(CUSTOM_220 ">" DEFAULT_SGR);
	while (line && (!ft_samestr(str, line)))
	{
		if (!ft_samestr("", line))
		{
			expand_line(token, token->shell, &line);
			ft_putstr_fd(line, fd);
		}
		ft_putchar_fd('\n', fd);
		free(line);
		line = readline(CUSTOM_220 ">" DEFAULT_SGR);
	}
	free(line);
	close(fd);
	return (filename);
}

void	stdin_redirection(t_token	*token)
{
	int	i;

	i = -1;
	token->last_inf_fd = -1;
	if (token->infiles)
	{
		while (token->infiles[++i])
		{
			if (access(token->infiles[i], R_OK))
				return (perror(token->infiles[i]), exit(1));
			token->last_inf_fd = open(token->infiles[i], O_RDONLY);
			if (token->last_inf_fd == -1)
			{
				printf("OPEN ERROR\n");
				return ;
			}
			if (token->infiles[i + 1])
				close(token->last_inf_fd);
		}
	}
	if (token->last_inf_fd != -1)
	{
		dup2(token->last_inf_fd, STDIN_FILENO);
		close(token->last_inf_fd);
	}
}
