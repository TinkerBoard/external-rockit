/*
 * Copyright 2020 Rockchip Electronics Co. LTD
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * src author: <mediapipe-team@google.com>
 * new author: modified by <rimon.xu@rock-chips.com> and <martin.cheng@rock-chips.com>
 *       date: 2020-03-19
 *  reference: https://github.com/google/mediapipe
 */

#ifndef SRC_RT_TASK_TASK_GRAPH_RTTASKNODE_H_
#define SRC_RT_TASK_TASK_GRAPH_RTTASKNODE_H_

#include "string.h"
#include <map>
#include <functional>

#include "rt_header.h"

#include "RTTaskNodeContext.h"
#include "RTTaskNodeContextManager.h"
#include "RTTaskNodeOptions.h"
#include "RTTaskNodeFactory.h"
#include "RTNodeCommon.h"

typedef struct outputStreamLinkMap {
    int outputStreamIndex;
    std::vector<int> linkIndexList;
} outputStreamLinkMap;

typedef struct _RTTaskNodeInfo {
    int nodeId;
    std::vector<int> inputList;
    std::vector<outputStreamLinkMap> outputList;
} RTTaskNodeInfo;

class RTBufferListener;
class RTInputStreamHandler;
class RTInputStreamManager;
class RTOutputStreamHandler;
class RTOutputStreamManager;
class RTSchedulerQueue;
class RTTaskNode {
 public:
    RTTaskNode();
    virtual ~RTTaskNode();

    RT_RET prepareForRun(RtMetaData* options,
                         std::function<void()> sourceNodeOpenedCallback,
                         std::function<void(RTTaskNodeContext *)> scheduleCallback);

    RT_RET cleanupAfterRun();

    INT32 getID() { return mNodeId; }

    RT_BOOL isSource() const;
    RT_BOOL isSink() const;
    INT32 numInputStreams() const;
    INT32 numOutputStreams() const;

    RT_RET processNode(RTTaskNodeContext *packet);
    bool closed();
    RT_BOOL isDone();
    RT_RET closeNode();
    RT_RET closeInputStreams();
    RT_RET closeOutputStreams();

    void setMaxInputStreamQueueSize(INT32 maxQueueSize);
    void setMaxBatchPrcoessSize(INT32 maxBatchSize);
    void setQueueSizeCallbacks(
            std::function<void(RTInputStreamManager*, bool*)> becomesFullCallback,
            std::function<void(RTInputStreamManager*, bool*)> becomesNotFullCallback,
            std::function<void(RTInputStreamManager*, bool*)> becomesEmptyCallback);

    RT_RET initialize(int node_id, RTTaskNodeInfo *nodeInfo) { return RT_OK; }

    RT_RET initialize(
            int nodeId,
            RTTaskNodeInfo        *nodeInfo,
            RTInputStreamManager  *inputManager,
            RTOutputStreamManager *outputManager);
    RT_RET initialize(int nodeId,
            RTTaskNodeInfo *nodeInfo,
            const std::vector<RTInputStreamManager *> &inputManagers,
            const std::vector<RTOutputStreamManager *> &outputManagers);

    RT_RET addStreamSource(
            INT32 streamId, RTOutputStreamManager *lastOutputManager);
    RT_RET addStreamSource(RTOutputStreamManager *lastOutputManager);
    RT_RET removeStreamSource(RTOutputStreamManager *outputManager);
    const std::vector<INT32> &getStreamSource() { return mSourceNodes; }

    void checkIfBecameReady();

    RT_BOOL tryToBeginScheduling();
    void schedulingLoop();
    void endScheduling();
    void nodeOpened();

    // Returns a pointer to the default calculator context that is used for
    // sequential execution. A source node should always reuse its default
    // calculator context.
    RTTaskNodeContext* getDefaultNodeContext() const {
        return mNodeContextManager.getDefaultNodeContext();
    }

    RTSchedulerQueue* getSchedulerQueue() const {
        return mSchedulerQueue;
    }

    // Sets the scheduler queue the node is assigned to.
    void setSchedulerQueue(RTSchedulerQueue* queue) {
      mSchedulerQueue = queue;
    }

    RtMetaData *getOptions() { return mOptions; }

 public:
    virtual RT_RET open(RTTaskNodeContext *context) = 0;
    virtual RT_RET process(RTTaskNodeContext *context) = 0;
    virtual RT_RET close(RTTaskNodeContext *context) = 0;
    virtual RT_RET invoke(RtMetaData *meta);

 protected:
    virtual RT_RET initSupportOptions() { return RT_OK; }
    virtual RT_RET invokeInternal(RtMetaData *meta) { return RT_ERR_UNSUPPORT; }

 protected:
    INT32 mNodeId;
    RTInputStreamHandler  *mInputHandler;
    RTOutputStreamHandler *mOutputHandler;

    RtMutex mMutex;

    INT32 mCurrentInScheduling = 0;
    INT32 mMaxInScheduling = 1;
    // SchedulingState incidates the current state of the node scheduling process.
    // There are four possible transitions:
    // (a) From kIdle to kScheduling.
    // Any thread that makes this transition becomes the scheduling thread and
    // will be responsible for preparing and scheduling all possible invocations.
    // (b) From kScheduling to kSchedulingPending.
    // Any thread, except the scheduling thread, can make this transition.
    // kSchedulingPending indicates that some recent changes require the
    // scheduling thread to recheck the node readiness after current scheduling
    // iteration.
    // (c) From kSchedulingPending to kScheduling.
    // Made by the scheduling thread to indicate that it has already caught up
    // with all the recent changes that can affect node readiness.
    // (d) From kScheduling to kIdle. Made by the scheduling thread when there is
    // no more scheduling work to be done.
    enum RTSchedulingState {
        kIdle = 0,        //
        kScheduling = 1,  //
        kSchedulingPending = 2
    };
    RTSchedulingState mSchedulingState = kIdle;
    RTTaskNodeContextManager mNodeContextManager;
    RtMetaData              *mOptions;
    std::function<void()> mSourceNodeOpenedCallback;
    // The status of the current Calculator that this CalculatorNode
    // is wrapping.  kStateActive is currently used only for source nodes.
    enum RTNodeStatus {
        kStateUninitialized = 0,
        kStatePrepared = 1,
        kStateOpened = 2,
        kStateActive = 3,
        kStateClosed = 4
    };
    RTNodeStatus mStatus = kStateUninitialized;
    RTSchedulerQueue *mSchedulerQueue = NULL;
    std::map<std::string/* name */, RTTaskNodeOption> mSupportOptions;
    std::vector<INT32> mSourceNodes;
};

#endif  // SRC_RT_TASK_TASK_GRAPH_RTTASKNODE_H_
