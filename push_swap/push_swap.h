/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mastie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 13:15:55 by mastie            #+#    #+#             */
/*   Updated: 2022/12/05 13:15:56 by mastie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include "ft_printf/ft_printf.h"

typedef struct s_pile
{
	int				value;
	int				rra;
	int				rrb;
	int				ra;
	int				rb;
	int				total;

	struct s_pile	*next;

}				t_pile;

typedef struct s_operator
{
	t_list		*args;
	t_pile		*a;
	t_pile		*b;

}				t_operator;

	/*OPERATIONS PARTS*/
void	sa(t_operator *operator);
void	sb(t_operator *operator);
void	ss(t_operator *operator);
void	pa(t_operator *operator);
void	pb(t_operator *operator);
void	ra(t_operator *operator, int print);
void	rb(t_operator *operator, int print);
void	rra(t_operator *operator, int print);
void	rrb(t_operator *operator, int print);
void	rr(t_operator *operator, int r_a, int r_b);
void	rrr(t_operator *operator, int r_ra, int r_rb);

	/*PARSER PARTS*/
int		parser(t_operator *operator, char **av, int ac);

	/*SOLVER PARTS*/
int		sorted(t_operator *operator);
void	solver(t_operator *operator);
void	solver_3(t_operator *operator);
void	solver_5(t_operator *operator);
int		nothing_supp(t_pile *to_test, t_pile *current);
void	reset_counter(t_pile *current);
int		current_is_new_min(t_operator *operator, t_pile *current);
int		current_is_new_max(t_operator *operator, t_pile *current);
int		current_max_is_head(t_operator *operator);
void	hit_counter(t_operator *operator);
void	extract_insert(t_operator *operator);
void	b_insert_counter(t_operator *operator, t_pile *current);
void	insert_lower_hit(t_operator *operator);
void	insert_this_one(t_operator *operator, int this_one);
void	rotate_superior_current_to_head(t_operator *operator, t_pile *current);
void	rotate_max_head(t_operator *operator);
void	rotate_the_max_to_head(t_operator *operator, int is_at);
void	rotate_old_max_to_head(t_operator *operator, t_pile *current);
void	rrb_or_rb(t_pile *current, int i_old_max, int b_lst_c);
void	act_for_this_one(t_operator *operator, t_pile *this_one);
void	a_extract_counter(t_operator *operator, t_pile *current, int i);

	/*FREE PARTS*/
void	free_char_tab(char **tab);
void	free_piles(t_operator *operator);

	/*HITS PARTS*/
void	a_hit_calculator(t_operator *operator, int position);
void	b_hit_calculator(t_operator *operator, int position, int from_position);

	/*LST PARTS*/
t_pile	*lst_new(int value);
int		lst_count(t_pile *head);
void	add_new_to_a(t_pile **a, t_pile *new);
void	print_piles(t_operator *operator);

#endif
