// src/pages/IntroPage.js
import React from 'react';
import HistogramChart from '../components/HistogramChart';
import { firstDataset, secondDataset, thirdDataset } from '../components/datasets';
import HistogramTimeChart from '../components/HistogramTimeChart';
import { dataset1Time, dataset2Time, dataset3Time } from '../components/datasetsTime';

const IntroPage = () => {
  return (
    <div style={{ padding: '1rem' }}>
      <h1>Maximal Clique Enumeration</h1>
      <p>
        <p>
      Maximal clique enumeration is a fundamental problem in graph theory with applications in social network analysis, bioinformatics, and recommendation systems. Identifying maximal cliques helps in understanding network structures, community detection, and various optimization problems.
        </p>
        <p>
      In this project, we implement and compare three different maximal clique enumeration algorithms to evaluate their performance on real-world datasets. These algorithms were chosen because they represent different theoretical approaches: worst-case complexity analysis, degeneracy ordering for sparse graphs, and arboricity-based methods. The goal is to analyze their computational efficiency and effectiveness in different graph structures. Maximal clique enumeration is a fundamental problem in graph theory with applications in social network analysis, bioinformatics, and recommendation systems. Identifying maximal cliques helps in understanding network structures, community detection, and various optimization problems.
        </p>
      </p>

      <h2>Clique Distribution Histograms</h2>
      <p>
        Below are three different datasets illustrating how clique sizes might be distributed in different graphs.
      </p>

      <HistogramChart
        data={firstDataset}
        title="Clique Size Distribution (Dataset 1)"
        color="#4f81bd"
      />

      <HistogramChart
        data={secondDataset}
        title="Clique Size Distribution (Dataset 2)"
        color="#c0504d"
      />

      <HistogramChart
        data={thirdDataset}
        title="Clique Size Distribution (Dataset 3)"
        color="#9bbb59"
      />

      {/* You could also add Time Analysis Histograms or other sections below */}
      <h2>Time Comparision Histograms</h2>
      <p>
        Below are three different datasets illustrating how clique sizes might be distributed in different graphs.
      </p>

      <HistogramTimeChart
        data={dataset1Time}
        title="Dataset 1 Time Comparison"
        color="#8884d8"
      />

      <HistogramTimeChart
        data={dataset2Time}
        title="Dataset 2 Time Comparison"
        color="#82ca9d"
      />

      <HistogramTimeChart
        data={dataset3Time}
        title="Dataset 3 Time Comparison"
        color="#ffc658"
      />
        <h2>Summary of Key Findings:</h2>
      <ul>
        <li>The efficiency of each algorithm depends on graph sparsity and structure.</li>
        <li>Bron-Kerbosch with degeneracy ordering performed best in sparse graphs.</li>
        <li>Applying these techniques to real-world applications such as fraud detection and network security.</li>
      </ul>
    </div>
  );
};

export default IntroPage;
