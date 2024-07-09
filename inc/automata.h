/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   automata.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 16:35:05 by jvasquez          #+#    #+#             */
/*   Updated: 2024/07/09 23:28:45 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AUTOMATA_H
# define AUTOMATA_H

typedef struct s_automata
{
	void	*data;
	char	**alphabet;
	char	**errors;
	char	*str;
	int		state;
	int		ostate;
	int		errorlen;
	int		i;
	int		j;
	void	(*fsa[20])(struct s_automata *a, void *data);
	void	(*fta[20][20])(struct	s_automata
			*a, void
			*data);
	int		(*get_state)(int state, int abc_idx);
}			t_automata;

//FTS

int			evaluate(t_automata *a);
void		free_alph_err(t_automata *a);

//splitter FT

int			splitter_get_state(int i, int j);
void		splitter_alphabet_init(t_automata *a);
void		splitter_errors_init(t_automata *a);
void		splitter_sactions_init(t_automata *a);
void		splitter_tactions_init(t_automata *a);
void		splitter_automata_init(t_automata *a, void *data);


//TOKENIZER FT

int			tokenizer_get_state(int i, int j);
void		tokenizer_alphabet_init(t_automata *a);
void		tokenizer_errors_init(t_automata *a);
void		tokenizer_sactions_init(t_automata *a);
void		tokenizer_tactions_init(t_automata *a);
void		tokenizer_automata_init(t_automata *a, void *data);

//ACTIONS

void		get_token(t_automata *a, void *data);

//STATES ENUMS

typedef enum e_SP_states
{
	SP_EMPTY,
	SP_PIPE,
	SP_LESS,
	SP_HEREDOC,
	SP_GREAT,
	SP_APPEND,
	SP_AMPLESAN,
	SP_DOUBLEQ,
	SP_SINGLEQ,
	SP_INVALID,
	SP_SPACEB,
	SP_SPACEW,
	SP_WORDS
}	t_SP_states;

typedef enum e_tk_states
{
	TK_EMPTY,
	TK_DOUBLEQ,
	TK_SINGLEQ,
	TK_PIPE,
	TK_INVALID,
	TK_SPACEB,
	TK_SPACEW,
	TK_WORDS
}	t_tk_states;

#endif