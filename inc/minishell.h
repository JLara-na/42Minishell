/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 20:40:50 by jlara-na          #+#    #+#             */
/*   Updated: 2024/09/24 20:42:30 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//-----------------------------------INCLUDE----------------------------------//

# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <dirent.h>
# include <signal.h>
# include <limits.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/wait.h>
# include "automata.h"
# include "../lib/libft/libft.h"
# include "readline/history.h"
# include "readline/readline.h"

//-----------------------------------DEFINES----------------------------------//

# ifndef FALSE
#  define FALSE 0
# endif

# ifndef TRUE
#  define TRUE 1
# endif

# ifndef SUCCESS
#  define SUCCESS 0
# endif

# ifndef ERROR
#  define ERROR 1
# endif

# ifndef CHILD
#  define CHILD 0
# endif

# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif

# ifndef ARG_MAX
#  define ARG_MAX 4096
# endif

typedef enum e_pipe_fd
{
	READ_END,
	WRITE_END
}	t_pipe_fd;

# ifndef M_SHELL_PROMPT
#  define M_SHELL_PROMPT "$minishell> "
# endif

# ifndef MSG_BYE
#  define MSG_BYE "Bye!\n"
# endif

//-----------------------------DEFINING STRUCTURES----------------------------//

typedef struct s_shell
{
	t_automata	splitter;	//automata para comprobar la validez
	t_automata	expander;	//automata para expandir la linea
	t_automata	tokenizer;	//automata para tokenizar
	t_tree		*token_tree;	//arbol que contiene las lineas entre pipes
	t_list		*enviroment;
	t_list		*export_env;
	pid_t		last_pid;
	int			child;		//VARIABLE PARA SABER SI EL PROCESO ES UN HIJO CON POSIBES PROCESOS HIIJOS
	int			exit_status;
	char		*readline;
	char		**default_env;
	char		**path_var; //Revisar si es necesario o no

}	t_shell;

typedef struct s_token
{
	t_shell		*shell;
	int			append;
	char		*line;		//Comandos con sus argumentos y redirecciones
	char		*cmd;		//El comando
	char		**args;		//Los argumentos (args[0] es el propio comando)
	char		**infiles;
	char		**heredoc;
	char		**outfiles;
	int			last_outf_fd; // AQUI
	int			last_inf_fd; // AQUI
	void		*data;
}	t_token;

//Enviroment variable (name, value)
typedef struct s_var
{
	char		*name;
	char		*value;
}	t_var;

//----------------------------------FUNCTIONS---------------------------------//

//Enviroment funcions

void	import_env(t_shell	*shell, char **env);
t_bool	find_var(void *content, void *context);
char	*find_value(t_list	*env, char	*name);
t_var	*create_var(char *name, char *value);


//Parsing functions

int		split_in_token_lines(t_shell	*shell);
void	tokenize_node(void	*token_ptr, void	*shell_ptr);
void	expand_token(void	*token_ptr, void	*shell_ptr);

//Executing functions

void	exe_minishell_recursive(t_tree	*tree);
void	wait_childs(t_token	*token, int twice);

void	child_pipe_redir(t_tree *node, t_token *token, int pid, int fd[2]);
void	exe_comand_node(t_token	*token, int pid);

void	stdout_redirection(t_token	*token);
void	stdin_redirection(t_token	*token);


int		is_built_in(char	*cmd);
int		exe_built_in(void	*data, void	*context);
void	exe_path_cmd(t_shell	*shell, t_token	*token);
void	exe_cmd_or_built(t_shell	*shell, t_token	*token);


//void	execute_token(void *data, void *context);
//int		exe_built_in(void	*data, void	*context);

//Built-in functions

int		built_in_cd(t_shell	*shell);
int		built_in_pwd(t_shell	*shell);
int		built_in_env(t_shell	*shell);
int		built_in_exit(t_shell	*shell);
int		built_in_echo(t_shell	*shell);
int		built_in_unset(t_shell	*shell);
int		built_in_export(t_shell *shell, t_token	*token);

//Utils

void	free_env(t_shell	*shell);
int		signals_init(void);

//Delete Later

void	print_tree(void *data);

//----------------------------------ERROR MSG---------------------------------//

# define ERROR_EXIT 	"EXIT\n"

//-----------------------------------DEFINES----------------------------------//

# define CD_BUILT		"cd"
# define ECHO_BUILT		"echo"
# define ENV_BUILT		"env"
# define EXIT_BUILT		"exit"
# define EXPORT_BUILT	"export"
# define PWD_BUILT		"pwd"
# define UNSET_BUILT	"unset"
# define PIPE_LINE		"|"
# define ESCAPE_2		2
# define ESCAPE_126		126
# define ESCAPE_127		127

//-----------------------------------ANSI EC----------------------------------//

# define FUNCTION_CLEAR         "\033[H"
# define CLEAR                  "\033[2J\033[1;1H"
# define DEF_COLOR              "\033[0m"
# define UP_ONE_LINE			"\033[F"

# define BLACK                  "\033[0;30m"
# define GRAY                   "\033[0;90m"
# define GRAY_BL                "\033[0;90;5m"

# define RED                    "\033[0;31m"
# define RED_B                  "\033[0;91m"
# define RED_BL                 "\033[0;91;5m"

# define GREEN                  "\033[0;32m"
# define GREEN_B                "\033[0;92m"
# define GREEN_BL               "\033[0;92;5m"

# define YELLOW                 "\033[0;33m"
# define YELLOW_B               "\033[0;93m"
# define YELLOW_BL              "\033[0;93;5m"

# define BLUE                   "\033[0;34m"
# define BLUE_B                 "\033[0;94m"
# define BLUE_BL                "\033[0;94;5m"

# define MAGENTA                "\033[0;35m"
# define MAGENTA_B              "\033[0;95m"
# define MAGENTA_BL             "\033[0;95;5m"

# define CYAN                   "\033[0;36m"
# define CYAN_B                 "\033[0;96m"
# define CYAN_BL                "\033[0;96;5m"

# define WHITE                  "\033[0;37m"
# define WHITE_B                "\033[0;97m"
# define WHITE_BL               "\033[0;97;5m"

# define CUSTOM_1				"\033[38:5:177m"
# define CUSTOM_2				"\033[38:5:208m"
# define CUSTOM_3				"\033[38:5:112m"
# define CUSTOM_4				"\033[38:5:101m"

# ifndef HEADER
#  define HEADER " _______ __         __         __           __ __\n\
|   |   |__|.-----.|__|.-----.|  |--.-----.|  |  |\n\
|       |  ||     ||  ||__ --||     |  -__||  |  |\n\
|__|_|__|__||__|__||__||_____||__|__|_____||__|__|\n\
\n\
            By \033[38:5:112mJLara-Na \033[0m& \033[38:5:177mBarJimen\n\033[0m\
\n\
You can use the command \"exit\" to leave minishell\n\n"
# endif

#endif