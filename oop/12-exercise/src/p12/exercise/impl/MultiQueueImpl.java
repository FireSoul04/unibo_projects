package p12.exercise.impl;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Set;

import p12.exercise.api.MultiQueue;

public class MultiQueueImpl<T, Q> implements MultiQueue<T, Q>{

    private final Map<Q, List<T>> multiQueue;
    
    public MultiQueueImpl() {
        multiQueue = new HashMap<>();
    }

    private void checkIfQueueIsAvailable(Q queue) {
        if (!multiQueue.containsKey(queue)) {
            throw new IllegalArgumentException();
        }
    }

    @Override
    public Set<Q> availableQueues() {
        return multiQueue.keySet();
    }

    @Override
    public void openNewQueue(Q queue) {
        if (!multiQueue.containsKey(queue)) {
            multiQueue.put(queue, new ArrayList<>());
        } else {
            throw new IllegalArgumentException();
        }
    }

    @Override
    public boolean isQueueEmpty(Q queue) throws IllegalArgumentException {
        checkIfQueueIsAvailable(queue);
        return multiQueue.get(queue).isEmpty();
    }

    @Override
    public void enqueue(T elem, Q queue) throws IllegalArgumentException {
        checkIfQueueIsAvailable(queue);
        multiQueue.get(queue).addLast(elem);
    }

    @Override
    public T dequeue(Q queue) throws IllegalArgumentException {
        checkIfQueueIsAvailable(queue);

        if (isQueueEmpty(queue)) {
            return null;
        }
        return multiQueue.get(queue).removeFirst();
    }

    @Override
    public Map<Q, T> dequeueOneFromAllQueues() {
        final Map<Q, T> dequeuedElementMap = new HashMap<>();

        for (final Q queueKey : multiQueue.keySet()) {
            final List<T> queue = multiQueue.get(queueKey);
            if (!queue.isEmpty()) {
                dequeuedElementMap.put(queueKey, queue.removeFirst());
            } else {
                dequeuedElementMap.put(queueKey, null);
            }
        }

        return dequeuedElementMap;
    }

    @Override
    public Set<T> allEnqueuedElements() {
        final Set<T> enqueuedElements = new HashSet<>();

        for (final List<T> queue : multiQueue.values()) {
            for (final T element : queue) {
                enqueuedElements.add(element);
            }
        }
        return enqueuedElements;
    }

    @Override
    public List<T> dequeueAllFromQueue(Q queue) throws IllegalArgumentException {
        checkIfQueueIsAvailable(queue);
        final List<T> dequeuedElements = new ArrayList<>();
  
        while (!multiQueue.get(queue).isEmpty()) {
            final T elem = multiQueue.get(queue).removeFirst();
            dequeuedElements.addLast(elem);
        }
        return dequeuedElements;
    }

    @Override
    public void closeQueueAndReallocate(Q queue) throws IllegalArgumentException, IllegalStateException {
        checkIfQueueIsAvailable(queue);
        final List<T> dequeuedElements = dequeueAllFromQueue(queue);
        final List<T> reallocatedQueue = findQueueToReallocate(queue);

        reallocatedQueue.addAll(dequeuedElements);
        multiQueue.remove(queue);
    }
    
    private List<T> findQueueToReallocate(Q queue) throws IllegalStateException {
        List<T> reallocatedQueue = null;
        for (final Q queueKey : multiQueue.keySet()) {
            if (queue != queueKey) {
                reallocatedQueue = multiQueue.get(queueKey);
            }
        }

        if (reallocatedQueue == null) {
            throw new IllegalStateException();
        } else {
            return reallocatedQueue;
        }
    }
}
