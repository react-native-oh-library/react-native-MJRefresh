import React, {Component} from 'react';
import {FlatList, Platform} from 'react-native';
class MJFlatList extends Component {
    render() {
        return <FlatList {...this.props} />;
    }
}

module.exports = (Platform.OS === 'ios' || Platform.OS === 'harmony') ? MJFlatList : FlatList;