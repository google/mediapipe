package com.quark.quamera.util;
/*
 * Copyright (C) 2005-2019 UCWeb Inc. All rights reserved.
 *  Description :
 *
 *  Creation    :  2021/2/20
 *  Author      : jiaming.wjm@alibaba-inc.com
 */

import androidx.annotation.RestrictTo;

import java.io.Closeable;

@RestrictTo(RestrictTo.Scope.LIBRARY_GROUP)
public class IOUtils {
    public static void safeClose(Closeable closeable) {
        if (closeable == null) {
            return;
        }
        try {
            closeable.close();
        } catch (Exception ignore) {
            CameraShould.fail();
        }
    }
}
