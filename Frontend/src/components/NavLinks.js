// src/components/NavLinks.js
import React from 'react';
import { NavLink } from 'react-router-dom';

const linkStyles = {
  color: '#fff',
  textDecoration: 'none',
  fontWeight: '500',
  transition: 'color 0.3s ease'
};

const NavLinks = () => {
  return (
    <div style={{ display: 'flex', gap: '2rem' }}>
      <NavLink
        to="/"
        end
        style={({ isActive }) => ({
          ...linkStyles,
          color: isActive ? '#ffa500' : '#fff'
        })}
      >
        Intro
      </NavLink>
      <NavLink
        to="/algo/1"
        style={({ isActive }) => ({
          ...linkStyles,
          color: isActive ? '#ffa500' : '#fff'
        })}
      >
        Procedure Clique
      </NavLink>
      <NavLink
        to="/algo/2"
        style={({ isActive }) => ({
          ...linkStyles,
          color: isActive ? '#ffa500' : '#fff'
        })}
      >
        Bron-Kerbosch
      </NavLink>
      <NavLink
        to="/algo/3"
        style={({ isActive }) => ({
          ...linkStyles,
          color: isActive ? '#ffa500' : '#fff'
        })}
      >
        Arboricity-Based Algorithm
      </NavLink>
    </div>
  );
};

export default NavLinks;
