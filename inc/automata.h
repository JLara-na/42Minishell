/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   automata.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 16:35:05 by jvasquez          #+#    #+#             */
/*   Updated: 2024/06/28 00:37:09 by jlara-na         ###   ########.fr       */
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

int			evaluate(t_automata *a);
int			get_state(int i, int j);
void		alphabet_init(t_automata *a);
void		errors_init(t_automata *a);
void		sactions_init(t_automata *a);
void		tactions_init(t_automata *a);
void		automata_init(t_automata *a, void *data);
void		free_alph_err(t_automata *a);

void		invalid_input(t_automata *a, void *data);
void		get_token(t_automata *a, void *data);

#endif