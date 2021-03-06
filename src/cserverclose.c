/* The command handler for "serverclose" hint.
 *
 * Copyright 2008 by Rainer Gerhards and Adiscon GmbH.
 *
 * This file is part of librelp.
 *
 * Librelp is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Librelp is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Librelp.  If not, see <http://www.gnu.org/licenses/>.
 *
 * A copy of the GPL can be found in the file "COPYING" in this distribution.
 *
 * If the terms of the GPL are unsuitable for your needs, you may obtain
 * a commercial license from Adiscon. Contact sales@adiscon.com for further
 * details.
 *
 * ALL CONTRIBUTORS PLEASE NOTE that by sending contributions, you assign
 * your copyright to Adiscon GmbH, Germany. This is necessary to permit the
 * dual-licensing set forth here. Our apologies for this inconvenience, but
 * we sincerely believe that the dual-licensing model helps us provide great
 * free software while at the same time obtaining some development funding.
 */
#include "config.h"
#include <stdlib.h>
#include <assert.h>
#include <sys/types.h>
#include "relp.h"
#include "cmdif.h"

/* as a quick hack, we provide our command handler prototypes here
 * right in front of the dispatcher. This saves us many otherwise-unneeded
 * header files (and will go away if we make them dynamically loadable).
 * alorbach, 2020-09-09
 */
/* core (protocol) commands */
PROTOTYPEcommand(C, Serverclose)

/* process the command
 * Note: this is a hint, so we do not (and MUST NOT) send a response.
 * rgerhards, 2008-03-31
 */
BEGINcommand(C, Serverclose)
	ENTER_RELPFUNC;
	pSess->pEngine->dbgprint((char*)"in serverclose command handler\n");

	/* We use state "broken" so that our usual recovery can kick in */
	relpSessSetSessState(pSess, eRelpSessState_BROKEN);
	iRet = RELP_RET_SESSION_CLOSED; /* indicate close condition */
ENDcommand
