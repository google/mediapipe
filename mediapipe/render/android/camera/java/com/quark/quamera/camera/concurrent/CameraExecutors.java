package com.quark.quamera.camera.concurrent;

import com.quark.quamera.util.SequentialExecutor;

//package com.quark.quamera.camera.concurrent;
///*
// * Copyright (C) 2005-2019 UCWeb Inc. All rights reserved.
// *  Description :
// *
// *  Creation    :  20-11-23
// *  Author      : jiaming.wjm@alibaba-inc.com
// */
//

public class CameraExecutors {

    private static SequentialExecutor sCameraTaskExecutor;

    private static SequentialExecutor sImageAnalyzeSubscriptHandler;

    public synchronized static SequentialExecutor getCameraTaskExecutor() {
        return sCameraTaskExecutor;
    }


    public static synchronized void init() {
        //do nothing
        sCameraTaskExecutor = new SequentialExecutor("camera_executor");
        sCameraTaskExecutor.start();

        sImageAnalyzeSubscriptHandler = new SequentialExecutor("image_analyze");
        sImageAnalyzeSubscriptHandler.start();
    }

    public synchronized static SequentialExecutor getImageAnalyzeSubscriptHandler() {
        return sImageAnalyzeSubscriptHandler;
    }


    public static synchronized void unInit() {
        if (sCameraTaskExecutor != null) {
            sCameraTaskExecutor.stop();
            sCameraTaskExecutor = null;
        }
        if (sImageAnalyzeSubscriptHandler != null) {
            sImageAnalyzeSubscriptHandler.stop();
            sImageAnalyzeSubscriptHandler = null;
        }
    }


}
