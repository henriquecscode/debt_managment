//
// Created by henri on 08/11/2020.
//

#ifndef DEBT_MANAGMENT_MAIN_H
#define DEBT_MANAGMENT_MAIN_H


/*!
 * @brief Creates a random economy and runs it
 */
void run();

/*!
 * @brief Creates various economies with different sizes and runs them
 * @details Exponentially increases the size of the economies and runs it. Meant to analyse the behavior of the ratio between final and inital debt as size increases
 */
void metaRun();

#endif //DEBT_MANAGMENT_MAIN_H
