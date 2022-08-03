package com.quark.quamera.camera.session;
/*
 * Copyright (C) 2005-2019 UCWeb Inc. All rights reserved.
 *  Description :
 *
 *  Creation    :  20-12-18
 *  Author      : jiaming.wjm@alibaba-inc.com
 */

import android.os.Handler;
import android.os.Looper;

import androidx.annotation.NonNull;

import com.quark.quamera.camera.camera.CameraErrorListenerHandlerWrapper;
import com.quark.quamera.camera.camera.ICameraErrorListener;
import com.quark.quamera.camera.session.config.CameraSelectConfig;


public class SessionConfig {


    private final PreviewConfig mPreviewConfig;

    private ImageCapture mCaptureConfig;

    private ICameraErrorListener mCameraErrorListener;

    private CameraSelectConfig mSelectConfig;


    public SessionConfig(@NonNull PreviewConfig previewConfig) {
        mPreviewConfig = previewConfig;
    }

    public void setCaptureConfig(ImageCapture captureConfig) {
        mCaptureConfig = captureConfig;
    }

    public void setSelectConfig(CameraSelectConfig selectConfig) {
        mSelectConfig = selectConfig;
    }

    public @NonNull
    PreviewConfig getPreviewConfig() {
        return mPreviewConfig;
    }

    public ImageCapture getImageCapture() {
        return mCaptureConfig;
    }

    public CameraSelectConfig getSelectConfig() {
        return mSelectConfig;
    }

    public void setCameraErrorListener(@NonNull ICameraErrorListener cameraErrorListener, Handler handler) {
        if (handler == null) {
            mCameraErrorListener = cameraErrorListener;
        } else {
            mCameraErrorListener = new CameraErrorListenerHandlerWrapper(new Handler(Looper.getMainLooper()), cameraErrorListener);
        }
    }

    public ICameraErrorListener getCameraErrorListener() {
        return mCameraErrorListener;
    }
}
