package com.quark.quamera.camera.session;
/*
 * Copyright (C) 2005-2019 UCWeb Inc. All rights reserved.
 *  Description :
 *
 *  Creation    :  20-12-19
 *  Author      : jiaming.wjm@alibaba-inc.com
 */

import android.hardware.Camera;
import android.hardware.camera2.CaptureRequest;

import androidx.annotation.NonNull;

import com.quark.quamera.camera.camera.Camera2Info;

import java.util.concurrent.Executor;

//TODO 后面要解决fill里面的属性都不支持的时候，就不需要重新发起repeatSession
public interface RepeatCaptureRequestConfig {


    void fillConfig(@NonNull Camera2Info cameraInfo,
                    @NonNull CaptureRequest.Builder builder);

    CameraCaptureCallback getCallback();

    default Executor getCallbackExecutor() {
        return null;
    }


}
