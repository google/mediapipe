package com.google.mediapipe.examples.posetracking_lindera;

import android.util.Log;

import com.google.mediapipe.solutions.lindera.BodyJoints;
import com.google.mediapipe.solutions.lindera.ComputerVisionPlugin;
import com.google.mediapipe.solutions.lindera.XYZPointWithConfidence;

public class ComputerVisionPluginImpl implements ComputerVisionPlugin {

    @Override
    public void bodyJoints(int timestamp, BodyJoints bodyJoints) {
        XYZPointWithConfidence nose = bodyJoints.nose;
        Log.v("ComputerVisionPluginImpl", String.format(

                "Lindera BodyJoint of Nose: x=%f, y=%f, z=%f", nose.x, nose.y, nose.z));
    }
}
