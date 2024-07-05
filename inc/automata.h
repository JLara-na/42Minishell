/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   automata.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 16:35:05 by jvasquez          #+#    #+#             */
/*   Updated: 2024/07/05 21:27:26 by jlara-na         ###   ########.fr       */
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

//CHECKER FT

int			checker_get_state(int i, int j);
void		checker_alphabet_init(t_automata *a);
void		checker_errors_init(t_automata *a);
void		checker_sactions_init(t_automata *a);
void		checker_tactions_init(t_automata *a);
void		checker_automata_init(t_automata *a, void *data);


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

typedef enum e_ch_states
{
	CH_EMPTY,
	CH_PIPE,
	CH_LESS,
	CH_HEREDOC,
	CH_GREAT,
	CH_APPEND,
	CH_AMPLESAN,
	CH_DOUBLEQ,
	CH_SINGLEQ,
	CH_INVALID,
	CH_SPACEB,
	CH_SPACEW,
	CH_WORDS
}	t_ch_states;

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