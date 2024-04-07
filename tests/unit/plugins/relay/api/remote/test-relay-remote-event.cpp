/*
 * test-relay-remote-event.cpp - test event functions for relay remote
 *
 * Copyright (C) 2024 Sébastien Helleu <flashcode@flashtux.org>
 *
 * This file is part of WeeChat, the extensible chat client.
 *
 * WeeChat is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * WeeChat is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with WeeChat.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "CppUTest/TestHarness.h"

#include "tests/tests.h"

extern "C"
{
#include <cjson/cJSON.h>
#include "src/core/core-config-file.h"
#include "src/plugins/relay/relay.h"
#include "src/plugins/relay/api/remote/relay-remote-event.h"
}

TEST_GROUP(RelayRemoteEvent)
{
};

/*
 * Tests functions:
 *   relay_remote_event_search_buffer
 */

TEST(RelayRemoteEvent, SearchBuffer)
{
    /* TODO: write tests */
}

/*
 * Tests functions:
 *   relay_remote_event_cb_buffer
 */

TEST(RelayRemoteEvent, CbBuffer)
{
    /* TODO: write tests */
}

/*
 * Tests functions:
 *   relay_remote_event_recv
 */

TEST(RelayRemoteEvent, Recv)
{
    /* TODO: write tests */
}
